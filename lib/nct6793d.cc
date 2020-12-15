/*
 * nct6793d.cc
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "nuvoton_chip_info.h"

namespace bsdsensors {

std::map<NuvotonTempSource, uint8_t> kNCT6793DTempSource{
    {kSourceSYSTIN, 1},        {kSourceCPUTIN, 2},
    {kSourceAUXTIN0, 3},       {kSourceAUXTIN1, 4},
    {kSourceAUXTIN2, 5},       {kSourceAUXTIN3, 6},
    {kSourceReserved, 7},      {kSourceSMBUSMASTER0, 8},
    {kSourceSMBUSMASTER1, 9},  {kSourceSMBUSMASTER2, 10},
    {kSourceSMBUSMASTER3, 11}, {kSourceSMBUSMASTER4, 12},
    {kSourceSMBUSMASTER5, 13}, {kSourceSMBUSMASTER6, 14},
    {kSourceSMBUSMASTER7, 15}, {kSourcePECI0, 16},
    {kSourcePECI1, 17},        {kSourcePCHCPUMAX, 18},
    {kSourcePCH, 19},          {kSourcePCHCPU, 20},
    {kSourcePCHMCH, 21},       {kSourceDIM0, 22},
    {kSourceDIM1, 23},         {kSourceDIM2, 24},
    {kSourceDIM3, 25},         {kSourceBYTE, 26},
    {kSource27, 27},           {kSource28, 28},
    {kSource29, 29},           {kSource30, 30},
    {kSource31, 31},
};

const NuvotonChipInfo kNCT6793D = {
    0xd121,
    "NCT6793D",
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
         NuvotonFanControlInfo{
             {1, 0x02, {7, 4}},
             {1, 0x09},
             true,
             {0, 0x04, {0}},
             {0, 0x01},
             {1, 0x00, {4, 0}},
             {0, 0x73},
             {0, 0x74, {7}},
             // Smart Fan I
             {true,
              /*thermal_cruise=*/
              {
                  .target_temp = {1, 0x01},
                  .tolerance = {1, 0x02, {2, 0}},
                  .start_value = {1, 0x06},
                  .stop_value = {1, 0x05},
                  .keep_min_output = {1, 0x00, {7}},
                  .stop_time = {1, 0x07},
                  .step_up_time = {1, 0x03},
                  .step_down_time = {1, 0x04},
                  .critical_temp = {1, 0x35},
              },
              /*speed_cruise=*/
              {
                  .target_speed_count_low = {1, 0x01},
                  .target_speed_count_high = {1, 0x0C, {3, 0}},
                  .tolerance_low = {1, 0x02, {2, 0}},
                  .tolerance_high = {1, 0x0C, {6, 4}},
                  .step_up_time = {1, 0x03},
                  .step_down_time = {1, 0x04},
                  .step_up_value = {1, 0x66, {7, 4}},
                  .step_down_value = {1, 0x66, {3, 0}},
              }},
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
         NuvotonFanControlInfo{
             {2, 0x02, {7, 4}},
             {2, 0x09},
             true,
             {0, 0x04, {1}},
             {0, 0x03},
             {2, 0x00, {4, 0}},
             {0, 0x75},
             {0, 0x76, {7}},
             // Smart Fan I
             {true,
              /*thermal_cruise=*/
              {
                  .target_temp = {2, 0x01},
                  .tolerance = {2, 0x02, {2, 0}},
                  .start_value = {2, 0x06},
                  .stop_value = {2, 0x05},
                  .keep_min_output = {2, 0x00, {7}},
                  .stop_time = {2, 0x07},
                  .step_up_time = {2, 0x03},
                  .step_down_time = {2, 0x04},
                  .critical_temp = {2, 0x35},
              },
              /*speed_cruise=*/
              {
                  .target_speed_count_low = {2, 0x01},
                  .target_speed_count_high = {2, 0x0C, {3, 0}},
                  .tolerance_low = {2, 0x02, {2, 0}},
                  .tolerance_high = {2, 0x0C, {6, 4}},
                  .step_up_time = {2, 0x03},
                  .step_down_time = {2, 0x04},
                  .step_up_value = {2, 0x66, {7, 4}},
                  .step_down_value = {2, 0x66, {3, 0}},
              }},
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
         NuvotonFanControlInfo{
             {3, 0x02, {7, 4}},
             {3, 0x09},
             true,
             {0, 0x04, {2}},
             {0, 0x11},
             {3, 0x00, {4, 0}},
             {0, 0x77},
             {0, 0x78, {7}},
             // Smart Fan I
             {true,
              /*thermal_cruise=*/
              {
                  .target_temp = {3, 0x01},
                  .tolerance = {3, 0x02, {2, 0}},
                  .start_value = {3, 0x06},
                  .stop_value = {3, 0x05},
                  .keep_min_output = {3, 0x00, {7}},
                  .stop_time = {3, 0x07},
                  .step_up_time = {3, 0x03},
                  .step_down_time = {3, 0x04},
                  .critical_temp = {3, 0x35},
              },
              /*speed_cruise=*/
              {
                  .target_speed_count_low = {3, 0x01},
                  .target_speed_count_high = {3, 0x0C, {3, 0}},
                  .tolerance_low = {3, 0x02, {2, 0}},
                  .tolerance_high = {3, 0x0C, {6, 4}},
                  .step_up_time = {3, 0x03},
                  .step_down_time = {3, 0x04},
                  .step_up_value = {3, 0x66, {7, 4}},
                  .step_down_value = {3, 0x66, {3, 0}},
              }},
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
         NuvotonFanControlInfo{
             {8, 0x02, {7, 4}},
             {8, 0x09},
             true,
             {0, 0x04, {3}},
             {0, 0x13},
             {8, 0x00, {4, 0}},
             {0, 0x79},
             {0, 0x7A, {7}},
             // Smart Fan I
             {true,
              /*thermal_cruise=*/
              {
                  .target_temp = {8, 0x01},
                  .tolerance = {8, 0x02, {2, 0}},
                  .start_value = {8, 0x06},
                  .stop_value = {8, 0x05},
                  .keep_min_output = {8, 0x00, {7}},
                  .stop_time = {8, 0x07},
                  .step_up_time = {8, 0x03},
                  .step_down_time = {8, 0x04},
                  .critical_temp = {8, 0x35},
              },
              /*speed_cruise=*/
              {
                  .target_speed_count_low = {8, 0x01},
                  .target_speed_count_high = {8, 0x0C, {3, 0}},
                  .tolerance_low = {8, 0x02, {2, 0}},
                  .tolerance_high = {8, 0x0C, {6, 4}},
                  .step_up_time = {8, 0x03},
                  .step_down_time = {8, 0x04},
                  .step_up_value = {8, 0x66, {7, 4}},
                  .step_down_value = {8, 0x66, {3, 0}},
              }},
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
         NuvotonFanControlInfo{
             {9, 0x02, {7, 4}},
             {9, 0x09},
             true,
             {0, 0x04, {4}},
             {0, 0x15},
             {9, 0x00, {4, 0}},
             {0, 0x7B},
             {0, 0x7C, {7}},
             // Smart Fan I
             {true,
              /*thermal_cruise=*/
              {
                  .target_temp = {9, 0x01},
                  .tolerance = {9, 0x02, {2, 0}},
                  .start_value = {9, 0x06},
                  .stop_value = {9, 0x05},
                  .keep_min_output = {9, 0x00, {7}},
                  .stop_time = {9, 0x07},
                  .step_up_time = {9, 0x03},
                  .step_down_time = {9, 0x04},
                  .critical_temp = {9, 0x35},
              },
              /*speed_cruise=*/
              {
                  .target_speed_count_low = {9, 0x01},
                  .target_speed_count_high = {9, 0x0C, {3, 0}},
                  .tolerance_low = {9, 0x02, {2, 0}},
                  .tolerance_high = {9, 0x0C, {6, 4}},
                  .step_up_time = {9, 0x03},
                  .step_down_time = {9, 0x04},
                  .step_up_value = {9, 0x66, {7, 4}},
                  .step_down_value = {9, 0x66, {3, 0}},
              }},
             // Smart Fan IV
             {true,
              // Control points
              {{{3, 0x21}, {3, 0x27}},
               {{3, 0x22}, {3, 0x28}},
               {{3, 0x23}, {3, 0x29}},
               {{3, 0x24}, {3, 0x2A}}}}}},
        {"AUXFAN3",
         {4, 0xCA},
         {4, 0xCB},
         {},
         {},
         NuvotonFanControlInfo{
             {10, 0x02, {7, 4}},
             {10, 0x09},
             true,
             {0, 0x04, {5}},
             {0, 0x17},
             {10, 0x00, {4, 0}},
             {0, 0x7D},
             {0, 0x7E, {7}},
             // Smart Fan I
             {true,
              /*thermal_cruise=*/
              {
                  .target_temp = {0xA, 0x01},
                  .tolerance = {0xA, 0x02, {2, 0}},
                  .start_value = {0xA, 0x06},
                  .stop_value = {0xA, 0x05},
                  .keep_min_output = {0xA, 0x00, {7}},
                  .stop_time = {0xA, 0x07},
                  .step_up_time = {0xA, 0x03},
                  .step_down_time = {0xA, 0x04},
                  .critical_temp = {0xA, 0x35},
              },
              /*speed_cruise=*/
              {
                  .target_speed_count_low = {0xA, 0x01},
                  .target_speed_count_high = {0xA, 0x0C, {3, 0}},
                  .tolerance_low = {0xA, 0x02, {2, 0}},
                  .tolerance_high = {0xA, 0x0C, {6, 4}},
                  .step_up_time = {0xA, 0x03},
                  .step_down_time = {0xA, 0x04},
                  .step_up_value = {0xA, 0x66, {7, 4}},
                  .step_down_value = {0xA, 0x66, {3, 0}},
              }},
             // Smart Fan IV
             {true,
              // Control points
              {{{3, 0x21}, {3, 0x27}},
               {{3, 0x22}, {3, 0x28}},
               {{3, 0x23}, {3, 0x29}},
               {{3, 0x24}, {3, 0x2A}}}}}},
    },
    // Temp sensors
    kNCT6793DTempSource,
    {
        {"SMIOVT1", {0, 0x27}, {}, false, true, {6, 0x21, {4, 0}}},
        {"SMIOVT2", {1, 0x50}, {1, 0x51, {7}}, false, true, {6, 0x22, {4, 0}}},
        {"SYSTIN", {4, 0x90}},
        {"CPUTIN", {4, 0x91}},
        {"AUXTIN0", {4, 0x92}},
        {"AUXTIN1", {4, 0x93}},
        {"AUXTIN2", {4, 0x94}},
        {"AUXTIN3", {4, 0x95}},
        {"PECI", {7, 0x20}, {7, 0x21, {1, 0}}, true},
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

RegisterChip<NuvotonChipInfo> kRegisterNCT6793D(kNCT6793D);

}  // namespace bsdsensors
