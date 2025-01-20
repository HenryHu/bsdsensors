/*
 * f71869a.cc
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "fintek_chip_info.h"

namespace bsdsensors {

FintekChipInfo kF71869A{
    {{0x1007, "F71869A"}},
    // Fans
    {
        {"FAN1",
         {0xA0},
         {0xA1},
         {0x2D},
         {0xA3},
         {0x96, {1, 0}},
         {0x96, {2, 0}}},
        {"FAN2", {0xB0}, {0xB1}, {0x2E}, {0xB3}, {0x96, {3, 2}}},
        {"FAN3", {0xC0}, {0xC1}, {0x2F}, {0xC3}, {0x96, {5, 4}}},
    },
    // Temps
    {
        {"TEMP1", {0x72}, {0x82}, {0x83}},
        {"TEMP2", {0x74}, {0x84}, {0x85}},
        {"TEMP3", {0x76}, {0x86}, {0x87}},
        {"CPU", {0x7A}},
        {"PCH", {0x7B}},
        {"MCH", {0x7C}},
        {"MAX_CPU_PCH_MCH", {0x7D}},
        {"PECI", {0x7E}},
        {"TSI0", {0xE0}},
        {"TSI1", {0xE1}},
        {"TSI2/CPU", {0xE3}, {}, {}, {0xE2}},
        {"TSI3/MCH", {0xE4}},
        {"TSI4/DIMM0", {0xE5}},
        {"TSI5/DIMM1", {0xE6}},
        {"TSI6/DIMM2", {0xE7}},
        {"TSI7/DIMM3", {0xE8}},
    },
    // Voltages
    {
        {"3Vcc", {0x20}, {0x30}, {0x31}},
        {"Vcore", {0x21}},
        {"Vin2", {0x22}},
        {"Vin3", {0x23}},
        {"Vin4", {0x24}},
        {"Vin5", {0x25}, {0x38}, {0x36}},
        {"Vin6", {0x26}, {0x39}, {0x37}},
        {"Vsb3V", {0x27}},
        {"Vbat", {0x28}},
    },
};

RegisterChip<FintekChipInfo> kRegisterF71869A(kF71869A);

}  // namespace bsdsensors
