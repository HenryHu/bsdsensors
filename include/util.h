/*
 * util.h
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#ifndef __BSDSENSORS_UTIL_H__
#define __BSDSENSORS_UTIL_H__

#include <cstdint>
#include <iostream>

#include <memory>

namespace bsdsensors {

class DumpAble {
   public:
    virtual void DumpInfo(std::ostream& out) = 0;
};

inline uint16_t Combine(uint8_t high, uint8_t low) {
    return ((uint16_t)high << 8) + low;
}

// Some bits in a byte
// [4:0] -> first: 4 width: 5
struct Bits {
    const int first, last;
    std::unique_ptr<Bits> next = nullptr;
    const int other_parts_len = 0;

    // Full byte
    Bits() : first(7), last(0) {}
    // One-bit flag
    Bits(int bit) : first(bit), last(bit) {}
    // General case
    Bits(int first, int last) : first(first), last(last) {}
    // Multiple ranges
    Bits(int first, int last, Bits&& next)
        : first(first),
          last(last),
          next(new Bits(next)),
          other_parts_len(next.total_width()) {}

    Bits(const Bits& another) : first(another.first), last(another.last) {
        if (another.next) {
            next = std::make_unique<Bits>(*another.next.get());
        }
    }

    bool full() const { return width() == 8; }
    int width() const { return first - last + 1; }
    int total_width() const { return width() + other_parts_len; }
};

extern uint8_t BitsFromByte(const Bits& bits, uint8_t byte);
extern uint8_t BitsToByte(const Bits& bits, uint8_t byte, uint8_t value);

}  // namespace bsdsensors

#endif  // __BSDSENSORS_UTIL_H__
