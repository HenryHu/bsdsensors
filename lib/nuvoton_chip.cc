/*
 * nuvoton_chip.cc
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "nuvoton_chip.h"
#include "super_io.h"
#include "port_io.h"
#include "nuvoton_chip_info.h"
#include "nuvoton_fan_speed.h"
#include "nuvoton_fan_control.h"
#include "nuvoton_temp_sensor.h"
#include "nuvoton_volt_sensor.h"
#include "util.h"

#include <unistd.h>
#include <iostream>
#include <iomanip>
using namespace std;

namespace bsdsensors {

using LogicalDeviceNo = uint8_t;

// Extended Function Enable Registers (EFERs)
const uint32_t kNuvotonPorts[] = {0x2E, 0x4E};

const SuperIO::AddressType kLogicalDeviceSelect = 0x07;
const LogicalDeviceNo kDeviceHM = 0x0B;

const SuperIO::AddressType kDeviceID = 0x20;
const SuperIO::AddressType kGlobalOption1 = 0x28;

const SuperIO::AddressType kLogicalDeviceEnabled = 0x30;
const SuperIO::AddressType kPortBaseAddress = 0x60;
const PortAddress kAddrPortOffset = 0x05;
const PortAddress kDataPortOffset = 0x06;

// const NuvotonChip::AddressType kConfigRegister = {0, 0x40};
const NuvotonChip::AddressType kBankSelect = {0, 0x4E};
const NuvotonChip::AddressType kChipID = {0, 0x58};
// const uint8_t kBankMask = 0x0f;
// const NuvotonChip::AddressType kPerBankMinAddr = 0x50;

class NuvotonLock {
   public:
    NuvotonLock(NuvotonChip* chip) : chip_(chip) { chip_->Enter(); }
    ~NuvotonLock() { chip_->Exit(); }

   private:
    NuvotonChip* chip_;
};

class NuvotonChipImpl : public NuvotonChip {
   public:
    NuvotonChipImpl()
        : port_io_(CreatePortIO()), entered_(false), info_(nullptr) {}
    ~NuvotonChipImpl() override {}

    // Enter Extended Function mode
    Status Enter() override {
        entered_ = true;
        auto status = io_->DirectWriteCommand(0x87);
        if (!status.ok()) return status;
        return io_->DirectWriteCommand(0x87);
    }

    // Exit Extended Function mode
    Status Exit() override {
        entered_ = false;
        return io_->DirectWriteCommand(0xaa);
    }

    bool Detect() override {
        if (!port_io_->Init().ok()) {
            return false;
        }
        for (const auto& port : kNuvotonPorts) {
            io_ = CreateSuperIO(port);
            if (!io_->Init().ok()) {
                continue;
            }

            {
                NuvotonLock lock(this);
                uint16_t id = 0;
                uint8_t result;
                if (!io_->ReadByte(kDeviceID, &result).ok()) {
                    continue;
                }
                id |= (uint16_t)result << 8;
                if (!io_->ReadByte(kDeviceID + 1, &result).ok()) {
                    continue;
                }
                id |= result;
                if (id != 0xffff && GetBaseAddress()) {
                    cout << "Found Nuvoton chip, ID: " << hex << "0x" << id
                         << " at 0x" << port << endl;

                    info_ = NuvotonChips.Find(id);
                    if (info_ != nullptr) {
                        cout << "Known Nuvoton Chip: " << info_->name << endl;
                        LoadSensors();
                        return true;
                    } else {
                        cout << "Unknown Nuvoton Chip" << endl;
                        return false;
                    }
                }
            }
        }
        io_.reset();
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
            cerr << "Logical device not enabled." << endl;
            return EnableDevice();
        }
        return OkStatus();
    }

    Status WriteByte(const NuvotonChip::AddressType& addr,
                     const uint8_t data) override {
        uint8_t orig = 0;
        if (!addr.bits.full()) {
            RETURN_IF_ERROR(ReadByte(addr, &orig));
        }
        RETURN_IF_ERROR(SelectBank(addr.bank));
        RETURN_IF_ERROR(port_io_->WriteByte(addr_port_, addr.addr));
        uint8_t my_part = data >> addr.other_parts_len;
        RETURN_IF_ERROR(port_io_->WriteByte(
            data_port_, BitsToByte(addr.bits, orig, my_part)));
        if (addr.next) {
            uint8_t other_part = data & ((1 << addr.other_parts_len) - 1);
            return WriteByte(*addr.next.get(), other_part);
        } else {
            return OkStatus();
        }
    }

    Status ReadByte(const NuvotonChip::AddressType& addr,
                    uint8_t* data) override {
        RETURN_IF_ERROR(SelectBank(addr.bank));
        RETURN_IF_ERROR(port_io_->WriteByte(addr_port_, addr.addr));
        uint8_t value;
        RETURN_IF_ERROR(port_io_->ReadByte(data_port_, &value));
        uint8_t my_part = BitsFromByte(addr.bits, value);
        if (addr.next) {
            uint8_t other_part;
            RETURN_IF_ERROR(ReadByte(*addr.next.get(), &other_part));
            *data = my_part << addr.other_parts_len | other_part;
        } else {
            *data = my_part;
        }
        return OkStatus();
    }

    Status ReadWord(const NuvotonChip::AddressType& addr, uint16_t* data) {
        uint8_t high, low;
        RETURN_IF_ERROR(ReadByte(addr, &low));
        NuvotonChip::AddressType high_addr = addr;
        high_addr.bank |= 0x80;
        RETURN_IF_ERROR(ReadByte(high_addr, &high));
        *data = Combine(high, low);
        return OkStatus();
    }

    Status SelectBank(uint8_t bank_no) {
        RETURN_IF_ERROR(port_io_->WriteByte(addr_port_, kBankSelect.addr));
        return port_io_->WriteByte(data_port_, bank_no);
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

        addr_port_ = port_base + kAddrPortOffset;
        data_port_ = port_base + kDataPortOffset;
        cout << "HM ports: 0x" << hex << addr_port_ << " 0x" << data_port_
             << endl;

        uint8_t value;
        io_->ReadByte(kGlobalOption1, &value);
        if (value & 0x10) {
            cerr << "Enable mapping" << endl;
            value &= ~0x10;
            io_->WriteByte(kGlobalOption1, value);
        }

        return true;
    }

    void DumpInfo(std::ostream& out) override {
        {
            NuvotonLock lock(this);
            CHECK(SelectDevice(kDeviceHM), "Fail to select logical device");
        }

        if (info_) {
            uint16_t vendor_id;
            CHECK(ReadWord(info_->vendor_id_addr, &vendor_id),
                  "fail to read vendor id");
            out << "Vendor ID, 0x5ca3 for Nuvoton: " << hex << vendor_id
                << endl;
        }

        uint8_t chip_id;
        CHECK(ReadByte(kChipID, &chip_id), "fail to read chip id");
        out << "Chip ID, usually 0xc1: " << hex << (int)chip_id << endl;

        for (int i = 0; i < fan_speeds_.size(); i++) {
            NuvotonFanSpeed& fan = *fan_speeds_[i];
            fan.DumpInfo(out);
            NuvotonFanControl& control = *fan_controls_[i];
            control.DumpInfo(out);
        }
        for (const auto& temp : temp_sensors_) {
            temp->DumpInfo(out);
        }
        NuvotonTempSource orig = temp_sensors_[0]->GetSource();
        for (int i = 8; i < 32; i++) {
            if (i == orig) continue;
            temp_sensors_[0]->SetSource((NuvotonTempSource)i);
            temp_sensors_[0]->DumpInfo(out);
        }
        temp_sensors_[0]->SetSource(orig);
        for (const auto& volt : volt_sensors_) {
            volt->DumpInfo(out);
        }
    }

    void DumpAll(ostream& out) {
        for (uint8_t bank = 0; bank < 11; bank++) {
            for (int i = 0; i < 256; i++) {
                uint8_t data;
                CHECK(ReadByte({bank, i}, &data), "Fail to read byte");
                if (data != 255 && data != 0) {
                    out << hex << (int)bank << "/" << setw(2) << i << ":" << dec
                        << setw(3) << (int)data << " ";
                }
                if ((i + 1) % 16 == 0) out << endl;
            }
        }
    }

    void LoadSensors() {
        for (const auto& fan : info_->fans) {
            fan_speeds_.push_back(CreateNuvotonFanSpeed(fan, this));
            fan_controls_.push_back(CreateNuvotonFanControl(fan.control, this));
        }
        for (const auto& temp : info_->temps) {
            temp_sensors_.push_back(
                CreateNuvotonTempSensor(temp, info_->temp_table, this));
        }
        for (const auto& volt : info_->volts) {
            volt_sensors_.push_back(CreateNuvotonVoltSensor(volt, this));
        }
    }

   private:
    std::unique_ptr<PortIO> port_io_;
    std::unique_ptr<SuperIO> io_;

    PortAddress addr_port_, data_port_;
    bool entered_;
    const NuvotonChipInfo* info_;

    std::vector<std::unique_ptr<NuvotonFanSpeed>> fan_speeds_;
    std::vector<std::unique_ptr<NuvotonFanControl>> fan_controls_;
    std::vector<std::unique_ptr<NuvotonTempSensor>> temp_sensors_;
    std::vector<std::unique_ptr<NuvotonVoltSensor>> volt_sensors_;
};

std::unique_ptr<NuvotonChip> CreateNuvotonChip() {
    return std::make_unique<NuvotonChipImpl>();
}

}  // namespace bsdsensors
