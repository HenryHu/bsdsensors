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

#include <memory>

class NuvotonChip : public Chip {
   public:
    using AddressType = std::pair<uint8_t, uint8_t>;

    bool Detect() override = 0;
    virtual void DumpInfo() = 0;

    virtual Status Enter() = 0;
    virtual Status Exit() = 0;

    virtual Status ReadByte(const AddressType& addr, uint8_t* data) = 0;
    virtual Status WriteByte(const AddressType& addr, const uint8_t data) = 0;
};

std::unique_ptr<NuvotonChip> CreateNuvotonChip();

#endif  // __BSDSENSORS_NUVOTON_CHIP_H__
