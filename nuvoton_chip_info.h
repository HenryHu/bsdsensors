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
#include <vector>

#include "nuvoton_chip.h"

struct NuvotonFanInfo {
    std::string name;
    NuvotonChip::AddressType rpm_high, rpm_low;
};

struct NuvotonChipInfo {
    std::string name;
    NuvotonChip::AddressType vendor_id_addr;
    std::vector<NuvotonFanInfo> fans;
};

const std::map<uint16_t, NuvotonChipInfo> kKnownNuvotonChips = {{
    0xd121,
    {"NCT6793D",
     {0, 0x4F},
     {{"SYSFAN", {4, 0xC0}, {4, 0xC1}},
      {"CPUFAN", {4, 0xC2}, {4, 0xC3}},
      {"AUXFAN0", {4, 0xC4}, {4, 0xC5}},
      {"AUXFAN1", {4, 0xC6}, {4, 0xC7}},
      {"AUXFAN2", {4, 0xC8}, {4, 0xC9}}}},
}};

#endif  // __BSDSENSORS_NUVOTON_CHIP_INFO_H__
