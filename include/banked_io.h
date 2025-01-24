/*
 * banked_io.h
 * Copyright (C) 2025 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#ifndef __BSDSENSORS_BANKED_IO_H__
#define __BSDSENSORS_BANKED_IO_H__

#include <cstdint>
#include <memory>

#include "status.h"

#include "address.h"
#include "port_io.h"

namespace bsdsensors {

class BankedIO {
   public:
    using AddressType = BankedAddress;
    virtual ~BankedIO() {}

    virtual Status Init() = 0;
    virtual Status ReadByte(const AddressType& addr, uint8_t* data) = 0;
    virtual Status ReadWord(const AddressType& addr, uint16_t* data) = 0;
    virtual Status WriteByte(const AddressType& addr, const uint8_t data) = 0;
};

std::unique_ptr<BankedIO> CreateBasicBankedIO(
    const PortAddress addr_port, const PortAddress data_port,
    const BankedAddress& bank_select, PortIO* port_io);
std::unique_ptr<BankedIO> CreateECSpacecBankedIO(
    const PortAddress page_port, const PortAddress index_port,
    const PortAddress data_port, PortIO* port_io);

}  // namespace bsdsensors

#endif  // __BSDSENSORS_BANKED_IO_H__

