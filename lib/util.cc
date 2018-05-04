/*
 * util.cc
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "util.h"

namespace bsdsensors {

// Return @bits in @byte.
uint8_t BitsFromByte(const Bits& bits, uint8_t byte) {
    assert(bits.first <= 8);
    assert(bits.last >= 0);
    assert(bits.first >= bits.last);

    if (bits.first - bits.last + 1 == 8) {
        return byte;
    }

    return (byte >> bits.last) & ((1 << (bits.first - bits.last + 1)) - 1);
}

// Return @byte with @bits replaced by @value.
uint8_t BitsToByte(const Bits& bits, uint8_t byte, uint8_t value) {
    assert(bits.first <= 8);
    assert(bits.last >= 0);
    assert(bits.first >= bits.last);

    if (bits.first - bits.last + 1 == 8) {
        return value;
    }

    uint8_t mask = (1 << (bits.first - bits.last + 1)) - 1;
    return (byte & ~(mask << bits.last)) | ((value & mask) << bits.last);
}

}  // namespace bsdsensors
