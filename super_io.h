/*
 * super_io.h
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#ifndef __BSDSENSORS_SUPER_IO_H__
#define __BSDSENSORS_SUPER_IO_H__

#include <cstdint>
#include <memory>

#include "status.h"

class SuperIO {
   public:
    using AddressType = uint32_t;
    virtual ~SuperIO() {}
    virtual Status Init() = 0;
    virtual Status ReadByte(const AddressType& address, uint8_t* data) = 0;
    virtual Status WriteByte(const AddressType& address,
                             const uint8_t data) = 0;
    virtual Status Enter() = 0;
    virtual Status Exit() = 0;
};

std::unique_ptr<SuperIO> CreateSuperIO(const uint32_t port);

class SuperIOLock {
   public:
    SuperIOLock(SuperIO* super_io);
    ~SuperIOLock();

   private:
    SuperIO* super_io_;
};

#endif  // __BSDSENSORS_SUPER_IO_H__
