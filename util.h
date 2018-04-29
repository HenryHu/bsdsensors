/*
 * util.h
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#ifndef __BSDSENSORS_UTIL_H__
#define __BSDSENSORS_UTIL_H__

#include <cstdint>

inline uint16_t Combine(uint8_t high, uint8_t low) {
    return ((uint16_t)high << 8) + low;
}

#endif  // __BSDSENSORS_UTIL_H__
