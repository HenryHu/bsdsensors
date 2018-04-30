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

struct NuvotonTempInfo {
    std::string name;
    bool has_frac_part;
    NuvotonChip::AddressType val_int, val_frac;
};

struct NuvotonChipInfo {
    std::string name;
    NuvotonChip::AddressType vendor_id_addr;
    std::vector<NuvotonFanInfo> fans;
    std::vector<NuvotonTempInfo> temps;
};

const std::map<uint16_t, NuvotonChipInfo> kKnownNuvotonChips = {
    {0xd121,
     {"NCT6793D",
      {0, 0x4F},
      {{"SYSFAN", {4, 0xC0}, {4, 0xC1}},
       {"CPUFAN", {4, 0xC2}, {4, 0xC3}},
       {"AUXFAN0", {4, 0xC4}, {4, 0xC5}},
       {"AUXFAN1", {4, 0xC6}, {4, 0xC7}},
       {"AUXFAN2", {4, 0xC8}, {4, 0xC9}},
       {"AUXFAN3", {4, 0xCA}, {4, 0xCB}}},
      {
          {"SYS", false, {0, 0x27}},
          {"CPU", true, {1, 0x50}, {1, 0x51}},
          {"SYSTIN", false, {4, 0x90}, {1, 0x51}},
          {"CPUTIN", false, {4, 0x91}, {1, 0x51}},
          {"AUXTIN0", false, {4, 0x92}, {1, 0x51}},
          {"AUXTIN1", false, {4, 0x93}, {1, 0x51}},
          {"AUXTIN2", false, {4, 0x94}, {1, 0x51}},
          {"AUXTIN3", false, {4, 0x95}, {1, 0x51}},
      }}}};

#endif  // __BSDSENSORS_NUVOTON_CHIP_INFO_H__
