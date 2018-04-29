/*
 * port_io.h
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#ifndef __BSDSENSORS_PORT_IO_H__
#define __BSDSENSORS_PORT_IO_H__

#include <cstdint>
#include <memory>

#include "status.h"

class PortIO {
   public:
    using AddressType = uint32_t;
    virtual ~PortIO() {}

    virtual Status Init() = 0;
    virtual Status ReadByte(const AddressType& address, uint8_t* data) = 0;
    virtual Status WriteByte(const AddressType& address,
                             const uint8_t data) = 0;
};

std::unique_ptr<PortIO> CreatePortIO();

#endif  // __BSDSENSORS_PORT_IO_H__
