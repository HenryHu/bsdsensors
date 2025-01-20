/*
 * fintek_chip.cc
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "fintek_chip.h"
#include "super_io.h"
#include "port_io.h"
#include "fintek_chip_info.h"
#include "fintek_temp_sensor.h"
#include "fintek_volt_sensor.h"
#include "fintek_fan.h"

namespace bsdsensors {

using LogicalDeviceNo = uint8_t;

constexpr uint8_t kEnterSequence[] = {0x87, 0x87};

const uint32_t kFintekPorts[] = {0x2E, 0x4E};

const SuperIO::AddressType kLogicalDeviceSelect = 0x07;
// Hardware monitoring
const LogicalDeviceNo kDeviceHM = 0x04;

const SuperIO::AddressType kDeviceID = 0x20;
const SuperIO::AddressType kVendorID = 0x23;

const uint16_t kVendorFintek = 0x1934;

const SuperIO::AddressType kLogicalDeviceEnabled = 0x30;
const SuperIO::AddressType kPortBaseAddress = 0x60;

class FintekLock {
   public:
    FintekLock(FintekChip* chip) : chip_(chip) { chip_->Enter(); }
    ~FintekLock() { chip_->Exit(); }

   private:
    FintekChip* chip_;
};

class FintekChipImpl : public FintekChip {
   public:
    FintekChipImpl()
        : port_io_(CreatePortIO()),
          entered_(false),
          info_(nullptr),
          name_("fintek") {}
    ~FintekChipImpl() override {}

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
        return io_->DirectWriteCommand(0xAA);
    }

    bool Detect() override {
        if (!port_io_->Init().ok()) {
            return false;
        }

        for (const auto& port : kFintekPorts) {
            io_ = CreateSuperIO(port);
            if (!io_->Init().ok()) {
                continue;
            }

            {
                FintekLock lock(this);

                uint16_t id = 0;
                uint8_t id_high, id_low;
                if (!io_->ReadByte(kDeviceID, &id_high).ok()) {
                    continue;
                }

                if (!io_->ReadByte(kDeviceID + 1, &id_low).ok()) {
                    continue;
                }
                id = Combine(id_high, id_low);
                if (id != 0xffff && GetBaseAddress()) {
                    std::cout << "Found Fintek chip, ID: " << std::hex << "0x"
                              << id << " at 0x" << port << std::endl;

                    info_ = GetKnownChips<FintekChipInfo>()->Find(id);
                    if (info_ != nullptr) {
                        std::cout << "Known Fintek Chip: " << info_->device_id_to_name.at(id)
                                  << std::endl;
                        LoadSensors();
                        return true;
                    } else {
                        std::cout << "Unknown Fintek Chip" << std::endl;
                        return false;
                    }
                }
            }
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
    bool GetBaseAddress() {
        assert(entered_);
        CHECK(SelectDevice(kDeviceHM), "Fail to select logical device");

        uint8_t base_high, base_low;
        if (!io_->ReadByte(kPortBaseAddress, &base_high).ok()) return false;
        if (!io_->ReadByte(kPortBaseAddress + 1, &base_low).ok()) return false;

        PortAddress port_base = Combine(base_high, base_low);
        if (port_base == 0xffff) {
            return false;
        }

        addr_port_ = port_base;
        data_port_ = port_base + 1;
        std::cout << "HM ports: 0x" << std::hex << addr_port_ << " 0x"
                  << data_port_ << std::endl;
        return true;
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
            FintekLock lock(this);
            CHECK(SelectDevice(kDeviceHM), "Fail to select logical device");

            uint8_t vendor_high, vendor_low;
            io_->ReadByte(kVendorID, &vendor_high);
            io_->ReadByte(kVendorID + 1, &vendor_low);
            uint16_t vendor = Combine(vendor_high, vendor_low);
            std::cerr << "Device vendor, usually " << std::hex << kVendorFintek
                      << ": " << vendor << std::endl;
        }

        for (const auto& temp : temp_sensors_) {
            temp->DumpInfo(out);
        }
        for (const auto& fan : fans_) {
            fan->DumpInfo(out);
        }
        for (const auto& volt : volt_sensors_) {
            volt->DumpInfo(out);
        }
    }

    void LoadSensors() {
        for (const auto& fan : info_->fans) {
            fans_.push_back(CreateFintekFan(fan, this));
        }
        for (const auto& temp : info_->temps) {
            temp_sensors_.push_back(CreateFintekTempSensor(temp, this));
        }
        for (const auto& volt : info_->volts) {
            volt_sensors_.push_back(CreateFintekVoltSensor(volt, this));
        }
    }

    Status GetSensorValues(SensorsProto* sensors) override {
        for (const auto& temp_sensor : temp_sensors_) {
            TemperatureProto* temp = sensors->add_temperatures();
            temp->set_name(temp_sensor->name());
            temp->set_value(temp_sensor->value());
        }
        for (const auto& volt_sensor : volt_sensors_) {
            VoltageProto* volt = sensors->add_voltages();
            volt->set_name(volt_sensor->name());
            volt->set_value(volt_sensor->value());
        }
        return OkStatus();
    }

   private:
    std::unique_ptr<PortIO> port_io_;
    std::unique_ptr<SuperIO> io_;

    PortAddress addr_port_, data_port_;
    bool entered_;
    const FintekChipInfo* info_;
    std::string name_;

    std::vector<std::unique_ptr<FintekFan>> fans_;
    std::vector<std::unique_ptr<FintekVoltSensor>> volt_sensors_;
    std::vector<std::unique_ptr<FintekTempSensor>> temp_sensors_;
};

std::unique_ptr<FintekChip> CreateFintekChip() {
    return std::make_unique<FintekChipImpl>();
}

}  // namespace bsdsensors
