/*
 * ite_chip.h
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#ifndef __BSDSENSORS_ITE_CHIP_H__
#define __BSDSENSORS_ITE_CHIP_H__

#include "chip.h"
#include "status.h"
#include "util.h"

namespace bsdsensors {

struct ITEAddress {
    int addr;
    Bits bits;
};

class ITEChip : public Chip {
   public:
    using AddressType = ITEAddress;

    bool Detect() override = 0;

    virtual Status Enter() = 0;
    virtual Status Exit() = 0;

    virtual Status ReadByte(const AddressType& addr, uint8_t* data) = 0;
    virtual Status WriteByte(const AddressType& addr, const uint8_t data) = 0;
};

std::unique_ptr<ITEChip> CreateITEChip();

}  // namespace bsdsensors

#endif  // __BSDSENSORS_ITE_CHIP_H__
