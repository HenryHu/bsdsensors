/*
 * super_io.cc
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "super_io.h"
#include "port_io.h"

class SuperIOImpl : public SuperIO {
   public:
    ~SuperIOImpl() override {}
    SuperIOImpl(const uint32_t port) : port_io_(CreatePortIO()), port_(port) {}

    Status Init() override { return port_io_->Init(); }

    Status Enter() override {
        auto status = port_io_->WriteByte(port_, 0x87);
        if (!status.ok()) return status;
        return port_io_->WriteByte(port_, 0x87);
    }

    Status Exit() override {
        auto status = port_io_->WriteByte(port_, 0xaa);
        if (!status.ok()) return status;
        status = port_io_->WriteByte(port_, 0x02);
        if (!status.ok()) return status;
        return port_io_->WriteByte(port_ + 1, 0x02);
    }

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

   private:
    std::unique_ptr<PortIO> port_io_;
    uint32_t port_;
};

std::unique_ptr<SuperIO> CreateSuperIO(const uint32_t port) {
    return std::make_unique<SuperIOImpl>(port);
}

SuperIOLock::SuperIOLock(SuperIO* super_io) : super_io_(super_io) {
    super_io_->Enter();
}
SuperIOLock::~SuperIOLock() { super_io_->Exit(); }
