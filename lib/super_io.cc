/*
 * super_io.cc
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "super_io.h"
#include "port_io.h"

namespace bsdsensors {

class SuperIOImpl : public SuperIO {
   public:
    ~SuperIOImpl() override {}
    SuperIOImpl(const uint32_t port, PortIO* port_io) : port_io_(port_io), port_(port) {}

    Status Init() override { return port_io_->Init(); }

    Status ReadByte(const AddressType& address, uint8_t* data) override {
        auto status = port_io_->WriteByte(port_, address);
        if (!status.ok()) return status;
        return port_io_->ReadByte(port_ + 1, data);
    }

    Status WriteByte(const AddressType& address, const uint8_t data) override {
        auto status = port_io_->WriteByte(port_, address);
        if (!status.ok()) return status;
        return port_io_->WriteByte(port_ + 1, data);
    }

    Status DirectWriteCommand(const uint8_t data) override {
        return port_io_->WriteByte(port_, data);
    }

    Status DirectWriteData(const uint8_t data) override {
        return port_io_->WriteByte(port_ + 1, data);
    }

   private:
    PortIO* port_io_;
    uint32_t port_;
};

std::unique_ptr<SuperIO> CreateSuperIO(const uint32_t port, PortIO* port_io) {
    return std::make_unique<SuperIOImpl>(port, port_io);
}

}  // namespace bsdsensors
