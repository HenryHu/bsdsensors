/*
 * nct6776f.cc
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "nuvoton_chip_info.h"
#include "nuvoton_temp_sensor.h"

namespace bsdsensors {

std::map<NuvotonTempSource, uint8_t> kNCT6776FTempSource{
    {kSourceSYSTIN, 1},        {kSourceCPUTIN, 2},
    {kSourceAUXTIN0, 3},       {kSourceSMBUSMASTER0, 4},
    {kSourceSMBUSMASTER1, 5},  {kSourceSMBUSMASTER2, 6},
    {kSourceSMBUSMASTER3, 7},  {kSourceSMBUSMASTER4, 8},
    {kSourceSMBUSMASTER5, 9},  {kSourceSMBUSMASTER6, 10},
    {kSourceSMBUSMASTER7, 11}, {kSourcePECI0, 12},
    {kSourcePECI1, 13},        {kSourcePCHCPUMAX, 14},
    {kSourcePCH, 15},          {kSourcePCHCPU, 16},
    {kSourcePCHMCH, 17},       {kSourceDIM0, 18},
    {kSourceDIM1, 19},         {kSourceDIM2, 20},
    {kSourceDIM3, 21},         {kSourceBYTE, 22},
};

NuvotonChipInfo kNCT6776F{
    0xC333,
    "NCT6776F/NCT6776D",
    {0, 0x4F},
    // Fan speed info
    {
        {"SYSFAN",
         // RPM
         {6, 0x56},
         {6, 0x57},
         // Fan Control
         // mode
         {{1, 0x02, {7, 4}},
          // out/w
          {1, 0x09},
          true,
          // out/type
          {0, 0x04, {0}},
          // duty
          {0, 0x01},
          // temp
          {1, 0x00, {4, 0}},
          {0, 0x73},
          {0, 0x74, {7}},
          // Smart Fan I
          {false},
          // Smart Fan IV
          {true,
           // Control points
           {{{1, 0x21}, {1, 0x27}},
            {{1, 0x22}, {1, 0x28}},
            {{1, 0x23}, {1, 0x29}},
            {{1, 0x24}, {1, 0x2A}}}}}},
        {"CPUFAN",
         {6, 0x58},
         {6, 0x59},
         // Fan Control
         {{2, 0x02, {7, 4}},
          {2, 0x09},
          false,
          {0, 0x04, {1}},
          {0, 0x03},
          {2, 0x00, {4, 0}},
          {0, 0x75},
          {0, 0x76, {7}},
          // Smart Fan I
          {false},
          // Smart Fan IV
          {true,
           // Control points
           {{{2, 0x21}, {2, 0x27}},
            {{2, 0x22}, {2, 0x28}},
            {{2, 0x23}, {2, 0x29}},
            {{2, 0x24}, {2, 0x2A}}}}}},
        {"AUXFAN",
         {6, 0x5A},
         {6, 0x5B},
         {{3, 0x02, {7, 4}},
          {3, 0x09},
          false,
          {0, 0x04, {2}},
          {0, 0x11},
          {3, 0x00, {4, 0}},
          {0, 0x77},
          {0, 0x78, {7}},
          // Smart Fan I
          {false},
          // Smart Fan IV
          {true,
           // Control points
           {{{3, 0x21}, {3, 0x27}},
            {{3, 0x22}, {3, 0x28}},
            {{3, 0x23}, {3, 0x29}},
            {{3, 0x24}, {3, 0x2A}}}}}},
    },
    // Temp sensors
    kNCT6776FTempSource,
    {
        // Source selectable
        {"SMIOVT1", {0, 0x27}, {}, false, true, {6, 0x21, {4, 0}}},
        {"SMIOVT2", {1, 0x50}, {1, 0x51, {7}}, false, true, {6, 0x22, {4, 0}}},
        {"SMIOVT3", {2, 0x50}, {2, 0x51, {7}}, false, true, {6, 0x23, {4, 0}}},
        {"SMIOVT4", {6, 0x2B}, {6, 0x2E, {0}}, false, true, {6, 0x24, {4, 0}}},
        {"SMIOVT5", {6, 0x2C}, {6, 0x2E, {1}}, false, true, {6, 0x25, {4, 0}}},
        {"SMIOVT6", {6, 0x2D}, {6, 0x2E, {2}}, false, true, {6, 0x26, {4, 0}}},
        // Fixed
        {"PECI", {7, 0x20}, {7, 0x21}, true},
        {"CPU_MCH_MAX", {4, 0x00}},
        {"PCH_CHIP", {4, 0x01}},
        {"PCH_CPU", {4, 0x02}, {4, 0x03, {7, 2}}},
        {"PCH_MCH", {4, 0x04}},
        {"DIM0", {4, 0x05}},
        {"DIM1", {4, 0x06}},
        {"DIM2", {4, 0x07}},
        {"DIM3", {4, 0x08}},
        // TODO: handle TSI temp (11 bits?)
        {"PCH_TSI0", {4, 0x09}, {4, 0x0A, {7, 5}}},
        {"PCH_TSI1", {4, 0x0B}, {4, 0x0C, {7, 5}}},
        {"PCH_TSI2", {4, 0x0D}, {4, 0x0E, {7, 5}}},
        {"PCH_TSI3", {4, 0x0F}, {4, 0x10, {7, 5}}},
        {"PCH_TSI4", {4, 0x11}, {4, 0x12, {7, 5}}},
        {"PCH_TSI5", {4, 0x13}, {4, 0x14, {7, 5}}},
        {"PCH_TSI6", {4, 0x15}, {4, 0x16, {7, 5}}},
        {"PCH_TSI7", {4, 0x17}, {4, 0x18, {7, 5}}},
        {"TSI_BYTE", {4, 0x19}, {4, 0x1A}},
    },
    // Volts
    {
        {"Vcore", {0, 0x20}, 2.0},
        {"AVcc", {0, 0x22}, 2.0},
        {"3Vcc", {0, 0x23}, 2.0},
        {"3Vsb", {5, 0x50}, 2.0},
        {"Vbat", {5, 0x51}, 2.0},
        {"Vin0", {0, 0x21}},
        {"Vin1", {0, 0x24}},
        {"Vin2", {0, 0x25}},
        {"Vin3", {0, 0x26}},
    }};

RegisterChip<NuvotonChipInfo> kRegisterNCT6776F(kNCT6776F, &NuvotonChips);

}  // namespace bsdsensors
