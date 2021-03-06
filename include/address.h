/*
 * address.h
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#ifndef __BSDSENSORS_ADDRESS_H__
#define __BSDSENSORS_ADDRESS_H__

#include "util.h"

#include <memory>

namespace bsdsensors {

struct BankedAddress {
    int bank = 0, addr = 0;
    Bits bits;
    bool valid;
    std::unique_ptr<BankedAddress> next;
    int other_parts_len = 0;

    BankedAddress() : valid(false) {}
    BankedAddress(int bank, int addr) : bank(bank), addr(addr), valid(true) {}
    BankedAddress(int bank, int addr, Bits bits)
        : bank(bank), addr(addr), bits(bits), valid(true) {}
    BankedAddress(int bank, int addr, Bits bits, BankedAddress next)
        : bank(bank),
          addr(addr),
          bits(bits),
          valid(true),
          next(std::make_unique<BankedAddress>(next)),
          other_parts_len(next.other_parts_len + next.bits.total_width()) {}

    BankedAddress(const BankedAddress& another)
        : bank(another.bank),
          addr(another.addr),
          bits(another.bits),
          valid(another.valid) {
        if (another.next) {
            next = std::make_unique<BankedAddress>(*another.next.get());
        }
    }
};

struct BasicAddress {
    int addr;
    Bits bits;
    bool valid;

    // Default: invalid
    BasicAddress() : valid(false) {}
    // Full byte
    BasicAddress(int addr) : addr(addr), valid(true) {}
    // Bits
    BasicAddress(int addr, Bits bits) : addr(addr), bits(bits), valid(true) {}
};

}  // namespace bsdsensors

#endif  // __BSDSENSORS_ADDRESS_H__
