/*
 * ite_chip.cc
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "ite_chip.h"
#include "super_io.h"
#include "port_io.h"
#include "ite_chip_info.h"
#include "ite_volt_sensor.h"
#include "ite_temp_sensor.h"
#include "ite_fan_speed.h"

namespace bsdsensors {

using LogicalDeviceNo = uint8_t;

constexpr uint8_t kEnterSequence[] = {0x87, 0x01, 0x55, 0x55};

const uint32_t kITEPorts[] = {0x2E, 0x4E};

const SuperIO::AddressType kConfigRegister = 0x02;

const SuperIO::AddressType kLogicalDeviceSelect = 0x07;
// Environment control
const LogicalDeviceNo kDeviceEC = 0x04;

const SuperIO::AddressType kDeviceID = 0x20;
const SuperIO::AddressType kDeviceVersion = 0x22;

const SuperIO::AddressType kLogicalDeviceEnabled = 0x30;
const SuperIO::AddressType kPortBaseAddress = 0x60;
const PortAddress kAddrPortOffset = 0x05;
const PortAddress kDataPortOffset = 0x06;

class ITELock {
   public:
    ITELock(ITEChip* chip) : chip_(chip) { chip_->Enter(); }
    ~ITELock() { chip_->Exit(); }

   private:
    ITEChip* chip_;
};

class ITEChipImpl : public ITEChip {
   public:
    ITEChipImpl(std::unique_ptr<PortIO> port_io)
        : port_io_(std::move(port_io)),
          entered_(false),
          info_(nullptr),
          name_("ite") {}
    ~ITEChipImpl() override {}

    std::string name() override { return name_; }
    void set_name(const std::string& name) override { this->name_ = name; }

    // Enter Extended Function mode
    Status Enter() override {
        entered_ = true;
        for (auto cmd : kEnterSequence) {
            RETURN_IF_ERROR(io_->DirectWriteCommand(cmd));
        }
        return OkStatus();
    }

    // Exit Extended Function mode
    Status Exit() override {
        entered_ = false;
        uint8_t data;
        RETURN_IF_ERROR(io_->ReadByte(kConfigRegister, &data));
        data |= 0x02;
        return io_->WriteByte(kConfigRegister, data);
    }

    bool Detect() override {
        if (!port_io_->Init().ok()) {
            return false;
        }

        for (const auto& port : kITEPorts) {
            io_ = CreateSuperIO(port, port_io_.get());
            if (!io_->Init().ok()) {
                continue;
            }

            Enter();

            uint16_t id = 0;
            uint8_t id_high, id_low;
            if (!io_->ReadByte(kDeviceID, &id_high).ok()) {
                continue;
            }

            if (!io_->ReadByte(kDeviceID + 1, &id_low).ok()) {
                continue;
            }
            id = Combine(id_high, id_low);
            if (id == 0xffff) continue;

            std::cout << "Found ITE chip, ID: " << std::hex << "0x"
                << id << " at 0x" << port << std::endl;

            GetBaseAddress();

            info_ = GetKnownChips<ITEChipInfo>()->Find(id);
            if (info_ == nullptr) {
                std::cout << "Unknown ITE Chip" << std::endl;
                Exit();
                return false;
            }

            std::cout << "Known ITE Chip: " << info_->device_id_to_name.at(id)
                << std::endl;
            LoadSensors();
            Exit();
            return true;
        }
        return false;
    }

    Status IsDeviceEnabled(bool* enabled) {
        uint8_t data;
        RETURN_IF_ERROR(io_->ReadByte(kLogicalDeviceEnabled, &data));
        *enabled = data & 0x1;
        return OkStatus();
    }

    Status EnableDevice() {
        uint8_t enabled;
        RETURN_IF_ERROR(io_->ReadByte(kLogicalDeviceEnabled, &enabled));

        enabled |= 0x1;
        return io_->WriteByte(kLogicalDeviceEnabled, enabled);
    }

    Status SelectDevice(const LogicalDeviceNo dev_no) {
        assert(entered_);
        RETURN_IF_ERROR(io_->WriteByte(kLogicalDeviceSelect, dev_no));
        bool enabled;
        RETURN_IF_ERROR(IsDeviceEnabled(&enabled));
        if (!enabled) {
            std::cerr << "Logical device not enabled." << std::endl;
            return EnableDevice();
        }
        return OkStatus();
    }

    // Locked
    void GetBaseAddress() {
        assert(entered_);
        CHECK(SelectDevice(kDeviceEC), "Fail to select logical device");

        uint8_t base_high, base_low;
        io_->ReadByte(kPortBaseAddress, &base_high);
        io_->ReadByte(kPortBaseAddress + 1, &base_low);

        PortAddress port_base = Combine(base_high, base_low);
        addr_port_ = port_base + kAddrPortOffset;
        data_port_ = port_base + kDataPortOffset;
        std::cout << "EC ports: 0x" << std::hex << addr_port_ << " 0x"
                  << data_port_ << std::endl;
    }

    void LoadSensors() {
        for (const auto& temp : info_->temps) {
            temp_sensors_.push_back(CreateITETempSensor(temp, this));
        }
        for (const auto& volt : info_->volts) {
            volt_sensors_.push_back(CreateITEVoltSensor(volt, this));
        }
        for (const auto& fan_speed : info_->fan_speeds) {
            fan_speeds_.push_back(CreateITEFanSpeed(fan_speed, this));
        }
    }

    Status WriteByte(const AddressType& addr, const uint8_t data) override {
        uint8_t orig = 0;
        if (!addr.bits.full()) {
            RETURN_IF_ERROR(ReadByte(addr, &orig));
        }
        RETURN_IF_ERROR(port_io_->WriteByte(addr_port_, addr.addr));
        return port_io_->WriteByte(data_port_,
                                   BitsToByte(addr.bits, orig, data));
    }

    Status ReadByte(const AddressType& addr, uint8_t* data) override {
        RETURN_IF_ERROR(port_io_->WriteByte(addr_port_, addr.addr));
        uint8_t value;
        RETURN_IF_ERROR(port_io_->ReadByte(data_port_, &value));
        *data = BitsFromByte(addr.bits, value);
        return OkStatus();
    }

    void DumpInfo(std::ostream& out) override {
        {
            ITELock lock(this);
            CHECK(SelectDevice(kDeviceEC), "Fail to select logical device");

            uint8_t version;
            io_->ReadByte(kDeviceVersion, &version);
            std::cerr << "Device version: " << std::hex << version << std::endl;

            for (auto& volt : volt_sensors_) {
                volt->DumpInfo(out);
            }
            for (auto& temp : temp_sensors_) {
                temp->DumpInfo(out);
            }
            for (auto& fan_speed : fan_speeds_) {
                fan_speed->DumpInfo(out);
            }
        }
    }

    Status GetSensorValues(SensorsProto* sensors) override {
        sensors->set_name(name_);
        for (auto& temp_sensor : temp_sensors_) {
            TemperatureProto& temp = *sensors->add_temperatures();
            temp.set_name(temp_sensor->name());
            temp.set_value(temp_sensor->value());
        }
        for (auto& volt_sensor : volt_sensors_) {
            VoltageProto& volt = *sensors->add_voltages();
            volt.set_name(volt_sensor->name());
            volt.set_value(volt_sensor->value());
        }
        for (auto& fan_speed : fan_speeds_) {
            FanProto& fan = *sensors->add_fans();
            fan.set_name(fan_speed->name());
            fan.mutable_speed()->set_value(fan_speed->value());
        }
        return OkStatus();
    }

   private:
    std::unique_ptr<PortIO> port_io_;
    std::unique_ptr<SuperIO> io_;

    PortAddress addr_port_, data_port_;
    bool entered_;
    const ITEChipInfo* info_;
    std::string name_;

    std::vector<std::unique_ptr<ITEVoltSensor>> volt_sensors_;
    std::vector<std::unique_ptr<ITETempSensor>> temp_sensors_;
    std::vector<std::unique_ptr<ITEFanSpeed>> fan_speeds_;
};

std::unique_ptr<ITEChip> CreateITEChip(std::unique_ptr<PortIO> port_io) {
    return std::make_unique<ITEChipImpl>(std::move(port_io));
}

}  // namespace bsdsensors
