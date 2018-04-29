/*
 * nuvoton_chip_info.h
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#ifndef __BSDSENSORS_NUVOTON_CHIP_INFO_H__
#define __BSDSENSORS_NUVOTON_CHIP_INFO_H__

#include <map>
#include <cstdint>
#include <string>

struct NuvotonChipInfo {
    std::string name;
};

const std::map<uint16_t, NuvotonChipInfo> kKnownNuvotonChips = {
    {0xd121, {"NCT6793D"}},
};

#endif  // __BSDSENSORS_NUVOTON_CHIP_INFO_H__
