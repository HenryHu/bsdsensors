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

namespace bsdsensors {

class SuperIO {
   public:
    using AddressType = uint32_t;
    virtual ~SuperIO() {}
    virtual Status Init() = 0;
    virtual Status ReadByte(const AddressType& address, uint8_t* data) = 0;
    virtual Status WriteByte(const AddressType& address,
                             const uint8_t data) = 0;
    virtual Status DirectWriteCommand(const uint8_t data) = 0;
    virtual Status DirectWriteData(const uint8_t data) = 0;
};

std::unique_ptr<SuperIO> CreateSuperIO(const uint32_t port);

}  // namespace bsdsensors

#endif  // __BSDSENSORS_SUPER_IO_H__
