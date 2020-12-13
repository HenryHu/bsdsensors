/*
 * nct5562d.cc
 * Copyright (C) 2020 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "nuvoton_chip_info.h"

namespace bsdsensors {

std::map<NuvotonTempSource, uint8_t> kNCT5562DTempSource{
    {kSourceCPUTIN, 2},        {kSourceAUXTIN0, 3},
    {kSourceSMBUSMASTER0, 8},  {kSourceSMBUSMASTER1, 9},
    {kSourceSMBUSMASTER2, 10}, {kSourceSMBUSMASTER3, 11},
    {kSourceSMBUSMASTER4, 12}, {kSourceSMBUSMASTER5, 13},
    {kSourceSMBUSMASTER6, 14}, {kSourceSMBUSMASTER7, 15},
    {kSourcePECI0, 16},        {kSourcePECI1, 17},
    {kSourcePCHCPUMAX, 18},    {kSourcePCH, 19},
    {kSourcePCHCPU, 20},       {kSourcePCHMCH, 21},
    {kSourceDIM0, 22},         {kSourceDIM1, 23},
    {kSourceDIM2, 24},         {kSourceDIM3, 25},
    {kSourceBYTE, 26},         {kSourcePECI0Calib, 27},
    {kSourcePECI1Calib, 28},   {kSourceVirtualTemp1, 29},
};

const NuvotonChipInfo kNCT5562D = {
    0xC911,
    "NCT5562D",
    /*vendor_id_addr=*/{0, 0x4F},
    // Fan speed info
    {
        {"SYSFAN",
         // RPM
         /*rpm_high=*/{4, 0xC0},  // documented
         /*rpm_low=*/{4, 0xC1},   // documented
         /*count=*/{},
         /*divisor=*/{},
         // Fan Control
         {/*mode_select=*/{1, 0x02, {7, 4}},   // documented
          /*output_value_write=*/{1, 0x09},    // documented
          /*support_dc=*/true,                 // documented
          /*output_type=*/{0, 0x04, {0}},      // documented
          /*output_value_read=*/{0, 0x01},     // documented
          /*temp_source=*/{1, 0x00, {4, 0}},   // documented
          /*temp_value_int=*/{0, 0x73},        // documented
          /*temp_value_frac=*/{0, 0x74, {7}},  // documented
          // Smart Fan I
          {false},
          // Smart Fan IV
          {true,
           // Control points
           {{/*temp=*/{1, 0x21}, /*power=*/{1, 0x27}},      // documented
            {/*temp=*/{1, 0x22}, /*power=*/{1, 0x28}},      // documented
            {/*temp=*/{1, 0x23}, /*power=*/{1, 0x29}},      // documented
            {/*temp=*/{1, 0x24}, /*power=*/{1, 0x2A}}}}}},  // documented
        {"CPUFAN",
         /*rpm_high=*/{4, 0xC2},  // documented
         /*rpm_low=*/{4, 0xC3},   // documented
         /*count=*/{},
         /*divisor=*/{},
         // Fan Control
         {/*mode_select=*/{2, 0x02, {7, 4}},  // documented
          /*output_value_write=*/{2, 0x09},   // documented
          /*support_dc=*/false,
          /*output_type=*/{},
          /*output_value_read=*/{0, 0x03},     // documented
          /*temp_source=*/{2, 0x00, {4, 0}},   // documented
          /*temp_value_int=*/{0, 0x75},        // documented
          /*temp_value_frac=*/{0, 0x76, {7}},  // documented
          // Smart Fan I
          {false},
          // Smart Fan IV
          {true,
           // Control points
           {{/*temp=*/{2, 0x21}, /*power=*/{2, 0x27}},      // documented
            {/*temp=*/{2, 0x22}, /*power=*/{2, 0x28}},      // documented
            {/*temp=*/{2, 0x23}, /*power=*/{2, 0x29}},      // documented
            {/*temp=*/{2, 0x24}, /*power=*/{2, 0x2A}}}}}},  // documented
        {"AUXFAN0",
         /*rpm_high=*/{4, 0xC4},  // documented
         /*rpm_low=*/{4, 0xC5},   // documented
         /*count=*/{},
         /*divisor=*/{},
         // Fan Control
         {/*mode_select=*/{3, 0x02, {7, 4}},  // documented
          /*output_value_write=*/{3, 0x09},   // documented
          /*support_dc=*/false,
          /*output_type=*/{},
          /*output_value_read=*/{0, 0x11},     // documented
          /*temp_source=*/{3, 0x00, {4, 0}},   // documented
          /*temp_value_int=*/{0, 0x77},        // documented
          /*temp_value_frac=*/{0, 0x78, {7}},  // documented
          // Smart Fan I
          {false},
          // Smart Fan IV
          {true,
           // Control points
           {{/*temp=*/{3, 0x21}, /*power=*/{3, 0x27}},      // documented
            {/*temp=*/{3, 0x22}, /*power=*/{3, 0x28}},      // documented
            {/*temp=*/{3, 0x23}, /*power=*/{3, 0x29}},      // documented
            {/*temp=*/{3, 0x24}, /*power=*/{3, 0x2A}}}}}},  // documented
        {
            "AUXFAN1",
            /*rpm_high=*/{4, 0xC6},  // documented
            /*rpm_low=*/{4, 0xC7},   // documented
            /*count=*/{},
            /*divisor=*/{},
            // Fan Control
            {
                /*mode_select=*/{},
                /*output_value_write=*/{},
                /*support_dc=*/false,
                /*output_type=*/{},
                /*output_value_read=*/{},
                /*temp_source=*/{},
                /*temp_value_int=*/{},
                /*temp_value_frac=*/{},
                // Smart Fan I
                {false},
                // Smart Fan IV
                {false},
            },
        },
    },
    // Temp sensors
    kNCT5562DTempSource,
    {
        {"SMIOVT1", /*val_int=*/{0, 0x27}, /*val_frac=*/{},  // documented
         /*has_peci_frac=*/false, /*can_select=*/true,
         /*select=*/{6, 0x21, {4, 0}}},     // documented
        {"SMIOVT2", /*val_int=*/{1, 0x50},  // documented
         /*val_frac=*/{1, 0x51, {7}},       // documented
         /*has_peci_frac=*/false, /*can_select=*/true,
         /*select=*/{6, 0x22, {4, 0}}},                   // documented
        {"CPUTIN", {4, 0x91}},                            // documented
        {"AUXTIN0", {4, 0x92}},                           // documented
        {"PECI0Calibration", {4, 0xF4}},                  // documented
        {"PCH_CPU_MAX", {4, 0x00}},                       // documented
        {"PCH", {4, 0x01}},                               // documented
        {"PCH_CPU", {4, 0x02}, {4, 0x03, {7, 2}}, true},  // documented
        {"MCH", {4, 0x04}},                               // documented
        {"DIM0", {4, 0x05}},                              // documented
        {"DIM1", {4, 0x06}},                              // documented
        {"DIM2", {4, 0x07}},                              // documented
        {"DIM3", {4, 0x08}},                              // documented
        {"TSI0", {4, 0x09}, {4, 0x0A, {7, 5}}},           // documented
        {"TSI1", {4, 0x0B}, {4, 0x0C, {7, 5}}},           // documented
        {"TSI2", {4, 0x0D}, {4, 0x0E, {7, 5}}},           // documented
        {"TSI3", {4, 0x0F}, {4, 0x10, {7, 5}}},           // documented
        {"TSI4", {4, 0x11}, {4, 0x12, {7, 5}}},           // documented
        {"TSI5", {4, 0x13}, {4, 0x14, {7, 5}}},           // documented
        {"TSI6", {4, 0x15}, {4, 0x16, {7, 5}}},           // documented
        {"TSI7", {4, 0x17}, {4, 0x18, {7, 5}}},           // documented
        {"BYTE", {4, 0x19}, {4, 0x1A}},                   // documented
    },
    // Volts
    // Notice that the multipliers depend on the actual resistances installed
    // on the motherboard, so it can be board-specific.
    {
        {"Vcore", {4, 0x80}, 2.0},  // documented
        {"AVcc", {4, 0x82}, 2.0},   // documented
        {"3Vcc", {4, 0x83}, 2.0},   // documented
        {"Vin4", {4, 0x86}},        // documented
        {"3Vsb", {4, 0x87}, 2.0},   // documented
        {"Vbat", {4, 0x88}},        // documented
        {"Vtt", {4, 0x89}},         // documented
        {"Vin2", {4, 0x8C}},        // documented
        {"Vin3", {4, 0x8D}},        // documented
    }};

RegisterChip<NuvotonChipInfo> kRegisterNCT5562D(kNCT5562D);

}  // namespace bsdsensors

