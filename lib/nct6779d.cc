/*
 * nct6779d.cc
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "nuvoton_chip_info.h"

namespace bsdsensors {

std::map<NuvotonTempSource, uint8_t> kNCT6779DTempSource{
    {NuvotonTempSource::kSourceSYSTIN, 1},        {NuvotonTempSource::kSourceCPUTIN, 2},
    {NuvotonTempSource::kSourceAUXTIN0, 3},       {NuvotonTempSource::kSourceAUXTIN1, 4},
    {NuvotonTempSource::kSourceAUXTIN2, 5},       {NuvotonTempSource::kSourceAUXTIN3, 6},
    {NuvotonTempSource::kSourceReserved, 7},      {NuvotonTempSource::kSourceSMBUSMASTER0, 8},
    {NuvotonTempSource::kSourceSMBUSMASTER1, 9},  {NuvotonTempSource::kSourceSMBUSMASTER2, 10},
    {NuvotonTempSource::kSourceSMBUSMASTER3, 11}, {NuvotonTempSource::kSourceSMBUSMASTER4, 12},
    {NuvotonTempSource::kSourceSMBUSMASTER5, 13}, {NuvotonTempSource::kSourceSMBUSMASTER6, 14},
    {NuvotonTempSource::kSourceSMBUSMASTER7, 15}, {NuvotonTempSource::kSourcePECI0, 16},
    {NuvotonTempSource::kSourcePECI1, 17},        {NuvotonTempSource::kSourcePCHCPUMAX, 18},
    {NuvotonTempSource::kSourcePCH, 19},          {NuvotonTempSource::kSourcePCHCPU, 20},
    {NuvotonTempSource::kSourcePCHMCH, 21},       {NuvotonTempSource::kSourceDIM0, 22},
    {NuvotonTempSource::kSourceDIM1, 23},         {NuvotonTempSource::kSourceDIM2, 24},
    {NuvotonTempSource::kSourceDIM3, 25},         {NuvotonTempSource::kSourceBYTE, 26},
    {NuvotonTempSource::kSource27, 27},           {NuvotonTempSource::kSource28, 28},
    {NuvotonTempSource::kSource29, 29},           {NuvotonTempSource::kSource30, 30},
    {NuvotonTempSource::kSource31, 31},
};

NuvotonChipInfo kNCT6779D{
    {{0xC561, "NCT6779D"}},
    {0, 0x4F},
    // Fan speed info
    {
        {"SYSFAN",
         // RPM
         {4, 0xC0},
         {4, 0xC1},
         {},
         {},
         // Fan Control
         NuvotonFanControlInfo{{1, 0x02, {7, 4}},
                               {1, 0x09},
                               {},
                               true,
                               {0, 0x04, {0}},
                               {0, 0x01},
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
         {4, 0xC2},
         {4, 0xC3},
         {},
         {},
         // Fan Control
         NuvotonFanControlInfo{{2, 0x02, {7, 4}},
                               {2, 0x09},
                               {},
                               false,
                               {0, 0x04},
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
        {"AUXFAN0",
         {4, 0xC4},
         {4, 0xC5},
         {},
         {},
         NuvotonFanControlInfo{{3, 0x02, {7, 4}},
                               {3, 0x09},
                               {},
                               false,
                               {0, 0x04},
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
        {"AUXFAN1",
         {4, 0xC6},
         {4, 0xC7},
         {},
         {},
         NuvotonFanControlInfo{{8, 0x02, {7, 4}},
                               {8, 0x09},
                               {},
                               false,
                               {0, 0x04},
                               {0, 0x13},
                               {8, 0x00, {4, 0}},
                               {0, 0x79},
                               {0, 0x7A, {7}},
                               // Smart Fan I
                               {false},
                               // Smart Fan IV
                               {true,
                                // Control points
                                {{{3, 0x21}, {3, 0x27}},
                                 {{3, 0x22}, {3, 0x28}},
                                 {{3, 0x23}, {3, 0x29}},
                                 {{3, 0x24}, {3, 0x2A}}}}}},
        {"AUXFAN2",
         {4, 0xC8},
         {4, 0xC9},
         {},
         {},
         NuvotonFanControlInfo{{9, 0x02, {7, 4}},
                               {9, 0x09},
                               {},
                               false,
                               {0, 0x04},
                               {0, 0x15},
                               {9, 0x00, {4, 0}},
                               {0, 0x7B},
                               {0, 0x7C, {7}},
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
    kNCT6779DTempSource,
    {
        {"SMIOVT1", {0, 0x27}, {}, false, true, {6, 0x21}},
        {"SMIOVT2", {1, 0x50}, {1, 0x51}, false, true, {6, 0x22}},
        {"SYSTIN", {4, 0x90}, {1, 0x51}},
        {"CPUTIN", {4, 0x91}, {1, 0x51}},
        {"AUXTIN0", {4, 0x92}, {1, 0x51}},
        {"AUXTIN1", {4, 0x93}, {1, 0x51}},
        {"AUXTIN2", {4, 0x94}, {1, 0x51}},
        {"AUXTIN3", {4, 0x95}, {1, 0x51}},
        {"PECI", {7, 0x20}, {7, 0x21}, true},
    },
    // Volts
    {
        {"Vcore", {4, 0x80}, 2.0},
        {"AVcc", {4, 0x82}, 2.0},
        {"3Vcc", {4, 0x83}, 2.0},
        {"3Vsb", {4, 0x87}, 2.0},
        {"Vbat", {4, 0x88}, 2.0},
        {"Vtt", {4, 0x89}},
        {"Vin0", {4, 0x84}},
        {"Vin1", {4, 0x81}},
        {"Vin2", {4, 0x8C}},
        {"Vin3", {4, 0x8D}},
        {"Vin4", {4, 0x86}},
        {"Vin5", {4, 0x8A}},
        {"Vin6", {4, 0x8B}},
        {"Vin7", {4, 0x8E}},
        {"Vin8", {4, 0x85}},
    }};

RegisterChip<NuvotonChipInfo> kRegisterNCT6779D(kNCT6779D);

}  // namespace bsdsensors
