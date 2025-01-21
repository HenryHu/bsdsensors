/*
 * fake_port_io.h
 * Copyright (C) 2025 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "fake_port_io.h"

#include <glog/logging.h>
#include <gtest/gtest.h>

#include <map>

namespace bsdsensors {

constexpr uint8_t kControlPort = 0x2E;
constexpr uint8_t kDataPort = 0x2F;
constexpr uint8_t kEnterValue = 0x87;
constexpr uint8_t kExitValue = 0xAA;

constexpr uint8_t kBankAddress = 0x4E;

constexpr uint16_t kHmAddr = 0x105;
constexpr uint16_t kHmData = 0x106;

class FakePortIOImpl : public FakePortIO {
  public:
    FakePortIOImpl(
        ControlRegisterTable registers, HmDataTable hm_data)
        : registers_(std::move(registers)), hm_data_(std::move(hm_data)) {}

    virtual ~FakePortIOImpl() {}

    Status Init() override { return OkStatus(); }
    Status ReadByte(const AddressType& address, uint8_t* data) override {
        Status result = OkStatus();;
        switch (address) {
            case kDataPort:
                result = DataRead(data);
                break;
            case kHmData:
                result = HmReadData(data);
                break;
            default:
                LOG(ERROR) << "Unexpected read at " << std::hex << address;
                return Status(EINVAL, "Unexpected read");
        };
        return result;
    }

    Status WriteByte(const AddressType& address,
            const uint8_t data) override {
        switch (address) {
            case kControlPort:
                return ControlWrite(data);
            case kDataPort:
                return DataWrite(data);
            case kHmAddr:
                return HmWriteAddr(data);
            case kHmData:
                return HmWriteData(data);
            default:
                LOG(ERROR) << "Unexpected write at " << std::hex << address;
                return Status(EINVAL, "Unexpected write");
        }
        return OkStatus();
    }

  private:
    enum class State {
        kInit0 = 0,
        kInit1 = 1,
        kEntered = 2,
    };

    Status ControlWrite(const uint8_t data) {
        switch (state_) {
            case State::kInit0:
                if (data == kEnterValue) state_ = State::kInit1;
                break;
            case State::kInit1:
                if (data == kEnterValue) state_ = State::kEntered;
                break;
            case State::kEntered:
                if (data == kExitValue) state_ = State::kInit0;
                register_addr_ = data;
                break;
        }
        return OkStatus();
    }

    Status DataRead(uint8_t* data) {
        const auto register_it = registers_.find(register_addr_);
        if (register_it == registers_.end()) {
            LOG(WARNING) << "no test data: CR " << std::hex << (int)register_addr_;
            *data = 0;
        } else {
            *data = register_it->second;
        }
        return OkStatus();
    }

    Status DataWrite(const uint8_t data) {
        if (state_ != State::kEntered) return OkStatus();
        registers_[register_addr_] = data;
        return OkStatus();
    }

    Status HmWriteAddr(const uint8_t data) {
        hm_addr_ = data;
        return OkStatus();
    }

    Status HmReadData(uint8_t* data) {
        const auto it = hm_data_.find(hm_bank_);
        if (it == hm_data_.end()) {
            LOG(WARNING) << "Unknown HM read at "
                << std::hex << (int) hm_bank_ << ", " << (int)hm_addr_;
            *data = 0;
            return OkStatus();
        }
        const auto data_it = it->second.find(hm_addr_);
        if (data_it == it->second.end()) {
            LOG(WARNING) << "Unknown HM read at "
                << std::hex << (int) hm_bank_ << ", " << (int)hm_addr_;
            *data = 0;
            return OkStatus();
        }
        *data = data_it->second;
        return OkStatus();
    }

    Status HmWriteData(const uint8_t data) {
        switch (hm_addr_) {
            case kBankAddress:
                hm_bank_ = data;
                break;
        }
        return OkStatus();
    }

    State state_ = State::kInit0;
    uint8_t register_addr_;
    uint8_t hm_addr_;
    uint8_t hm_bank_;
    std::map<uint8_t, uint8_t> registers_;
    std::map<uint8_t, std::map<uint8_t, uint8_t>> hm_data_;
};

std::unique_ptr<FakePortIO> CreateFakePortIO(
        ControlRegisterTable registers, HmDataTable hm_data) {
    return std::make_unique<FakePortIOImpl>(std::move(registers),
            std::move(hm_data));
}

}
