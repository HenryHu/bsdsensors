/*
 * nct6627ud.cc
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "nuvoton_chip_info.h"

namespace bsdsensors {

const NuvotonChipInfo kNCT6627UD{
    0xA230,
    "NCT6627UD/W83627UHG",
    {0, 0x4F},
    // Fan speed info
    {{"CPUFAN",
      {},
      {},
      {0, 0x28},
      {0, 0x5D, {6}, {0, 0x47, {7, 6}}},
      // Fan Control
      {{0, 0x04, {5, 4}},
       {0, 0x03},
       true,
       {0, 0x04, {1}},
       {0, 0x03},
       {0, 0x49, {2, 0}},
       {1, 0x50},
       {1, 0x51, {7}},
       // Smart Fan I
       {false},
       // Smart Fan IV
       {false}}},
     {"SYSFAN",
      // RPM
      {},
      {},
      {0, 0x29},
      {0, 0x5D, {5}, {0, 0x47, {5, 4}}},
      // Fan Control
      {{0, 0x04, {3, 2}},
       {0, 0x01},
       true,
       {0, 0x04, {0}},
       {0, 0x01},
       {0, 0x4A, {7, 5}},
       {2, 0x50},
       {2, 0x51, {7}},
       // Smart Fan I
       {false},
       // Smart Fan IV
       {false}}}},
    // Temp sensors
    // Not used, different mapping for different sources
    {},
    {
        {"SYSTIN", {0, 0x27}},
    },
    // Volts
    {
        {"Vcore", {0, 0x20}, 2.0},
        {"AVcc", {0, 0x22}, 2.0},
        {"5Vcc", {0, 0x23}},
        {"5Vsb", {5, 0x50}},
        {"Vbat", {5, 0x51}},
        {"Vin0", {0, 0x21}},
        {"Vin1", {0, 0x24}},
        {"Vin2", {0, 0x25}},
    }};

RegisterChip<NuvotonChipInfo> kRegisterNCT6627UD(kNCT6627UD, &NuvotonChips);

}  // namespace bsdsensors
