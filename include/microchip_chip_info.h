/*
 * microchip_chip_info.h
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#ifndef __BSDSENSORS_MICROCHIP_CHIP_INFO_H__
#define __BSDSENSORS_MICROCHIP_CHIP_INFO_H__

#include "chip_info.h"

#include <string>

namespace bsdsensors {

struct MicrochipChipInfo {
    uint16_t device_id;
    std::string name;
};

extern KnownChips<MicrochipChipInfo> MicrochipChips;

}  // namespace bsdsensors

#endif  // __BSDSENSORS_MICROCHIP_CHIP_INFO_H__
