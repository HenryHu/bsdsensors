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

#include <memory>

namespace bsdsensors {

struct NuvotonAddress {
    int bank = 0, addr = 0;
    Bits bits;
    bool valid;
    std::unique_ptr<NuvotonAddress> next;
    int other_parts_len = 0;

    NuvotonAddress() : valid(false) {}
    NuvotonAddress(int bank, int addr) : bank(bank), addr(addr), valid(true) {}
    NuvotonAddress(int bank, int addr, Bits bits)
        : bank(bank), addr(addr), bits(bits), valid(true) {}
    NuvotonAddress(int bank, int addr, Bits bits, NuvotonAddress next)
        : bank(bank),
          addr(addr),
          bits(bits),
          valid(true),
          next(std::make_unique<NuvotonAddress>(next)),
          other_parts_len(next.other_parts_len + next.bits.total_width()) {}

    NuvotonAddress(const NuvotonAddress& another)
        : bank(another.bank),
          addr(another.addr),
          bits(another.bits),
          valid(another.valid) {
        if (another.next) {
            next = std::make_unique<NuvotonAddress>(*another.next.get());
        }
    }
};

class NuvotonChip : public Chip {
   public:
    using AddressType = NuvotonAddress;

    bool Detect() override = 0;

    virtual Status Enter() = 0;
    virtual Status Exit() = 0;

    virtual Status ReadByte(const AddressType& addr, uint8_t* data) = 0;
    virtual Status WriteByte(const AddressType& addr, const uint8_t data) = 0;
};

std::unique_ptr<NuvotonChip> CreateNuvotonChip();

}  // namespace bsdsensors

#endif  // __BSDSENSORS_NUVOTON_CHIP_H__
