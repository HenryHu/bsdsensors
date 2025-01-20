/*
 * nuvoton_chip.h
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#ifndef __BSDSENSORS_NUVOTON_CHIP_H__
#define __BSDSENSORS_NUVOTON_CHIP_H__

#include "chip.h"
#include "status.h"
#include "util.h"
#include "address.h"
#include "port_io.h"

#include <memory>

namespace bsdsensors {

using NuvotonAddress = BankedAddress;

class NuvotonChip : public Chip {
  public:
    using AddressType = NuvotonAddress;

    virtual ~NuvotonChip() {}

    virtual Status Enter() = 0;
    virtual Status Exit() = 0;

    virtual Status ReadByte(const AddressType& addr, uint8_t* data) = 0;
    virtual Status WriteByte(const AddressType& addr, const uint8_t data) = 0;
    // One way to read word for Nuvoton chip: split it between 2 bytes, which is
    // represented as addr (high part) and addr.next (low part) here.
    virtual Status ReadWord2(const AddressType& addr, uint16_t* data) = 0;
};

std::unique_ptr<NuvotonChip> CreateNuvotonChip(std::unique_ptr<PortIO> port_io = CreatePortIO());

}  // namespace bsdsensors

#endif  // __BSDSENSORS_NUVOTON_CHIP_H__
