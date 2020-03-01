/*
 * fintek_chip.h
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#ifndef __BSDSENSORS_FINTEK_CHIP_H__
#define __BSDSENSORS_FINTEK_CHIP_H__

#include "chip.h"
#include "status.h"
#include "util.h"
#include "address.h"

namespace bsdsensors {

using FintekAddress = BasicAddress;

class FintekChip : public Chip {
  public:
    using AddressType = BasicAddress;

    virtual ~FintekChip() {}

    virtual Status Enter() = 0;
    virtual Status Exit() = 0;

    virtual Status ReadByte(const AddressType& addr, uint8_t* data) = 0;
    virtual Status WriteByte(const AddressType& addr, const uint8_t data) = 0;
};

std::unique_ptr<FintekChip> CreateFintekChip();

}  // namespace bsdsensors

#endif  // __BSDSENSORS_FINTEK_CHIP_H__
