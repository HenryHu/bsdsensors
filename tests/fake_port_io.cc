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
constexpr uint8_t kInitValue = 0x87;

class FakePortIOImpl : public FakePortIO {
  public:
    FakePortIOImpl(std::map<uint8_t, uint8_t> registers)
        : registers_(std::move(registers)) {}

    virtual ~FakePortIOImpl() {}

    Status Init() override { return OkStatus(); }
    Status ReadByte(const AddressType& address, uint8_t* data) override {
        if (address == kDataPort) {
            const auto register_it = registers_.find(register_addr_);
            if (register_it == registers_.end()) {
                LOG(WARNING) << "no test data: CR " << std::hex << (int)register_addr_;
                *data = 0;
            } else {
                *data = register_it->second;
            }
        }
        LOG(INFO) << "Reading from " << std::hex << address << " result " << (int)*data;
        return OkStatus();
    }

    Status WriteByte(const AddressType& address,
            const uint8_t data) override {
        LOG(INFO) << "Writing " << std::hex << (int)data << " to " << address;
        switch (address) {
            case kControlPort:
                return ControlWrite(data);
            case kDataPort:
                return DataWrite(data);
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
                if (data == kInitValue) state_ = State::kInit1;
                break;
            case State::kInit1:
                if (data == kInitValue) state_ = State::kEntered;
                break;
            case State::kEntered:
                register_addr_ = data;
                break;
        }
        return OkStatus();
    }

    Status DataWrite(const uint8_t data) {
        if (state_ != State::kEntered) return OkStatus();
        registers_[register_addr_] = data;
        return OkStatus();
    }

    State state_ = State::kInit0;
    uint8_t register_addr_;
    std::map<uint8_t, uint8_t> registers_;
};

std::unique_ptr<FakePortIO> CreateFakePortIO(
        std::map<uint8_t, uint8_t> registers) {
    return std::make_unique<FakePortIOImpl>(registers);
}

}
