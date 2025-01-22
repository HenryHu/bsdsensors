/*
 * nct5532d.cc
 * Copyright (C) 2025 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "nuvoton_chip_info.h"

namespace bsdsensors {

std::map<NuvotonTempSource, uint8_t> kNCT5532DTempSource{
        {NuvotonTempSource::kSourceSYSTIN, 1},
        {NuvotonTempSource::kSourceCPUTIN, 2},
        {NuvotonTempSource::kSourceAUXTIN0, 3},
        {NuvotonTempSource::kSourceAUXTIN1, 4},
        {NuvotonTempSource::kSourceAUXTIN2, 5},
        {NuvotonTempSource::kSourceVirtualTemp1, 6},
        {NuvotonTempSource::kSourceSMBUSMASTER0, 8},
        {NuvotonTempSource::kSourceSMBUSMASTER1, 9},
        {NuvotonTempSource::kSourcePECI0, 16},
        {NuvotonTempSource::kSourcePECI1, 17},
        {NuvotonTempSource::kSourcePCHCPUMAX, 18},
        {NuvotonTempSource::kSourcePCH, 19},
        {NuvotonTempSource::kSourcePCHCPU, 20},
        {NuvotonTempSource::kSourcePCHMCH, 21},
        {NuvotonTempSource::kSourceDIM0, 22},
        {NuvotonTempSource::kSourceDIM1, 23},
        {NuvotonTempSource::kSourceDIM2, 24},
        {NuvotonTempSource::kSourceDIM3, 25},
        {NuvotonTempSource::kSourceBYTE, 26},
};

const NuvotonChipInfo kNCT5532D = {
    {{0xC561, "NCT5532D"}},
    /*vendor_id_addr=*/{0, 0x4F},
    // Fan speed info
    {
        {
            .name = "SYSFAN",
            .rpm_high = {4, 0xC0}, .rpm_low = {4, 0xC1},
            .count = {4, 0xB0, /*bits=*/{}, /*next=*/{4, 0xB1, /*bits=*/{4, 0}}},
            .control = NuvotonFanControlInfo{
                .mode_select = {1, 0x02, {7, 4}},
                .output_value_write = {1, 0x09},
                .output_value_write_dc = {1, 0x09, {7, 2}},
                .support_dc = true,
                .output_type = {0, 0x04, {0}},
                .output_value_read = {0, 0x01},
                .temp_source = {1, 0x00, {4, 0}},
                .temp_value_int = {0, 0x73},
                .temp_value_frac = {0, 0x74, {7}},
                .smart_fan = {.available = true,
                    .thermal_cruise = {
                        .target_temp = {1, 0x01},
                        .tolerance = {1, 0x02, {2, 0}},
                        .start_value = {1, 0x06},
                        .stop_value = {1, 0x05},
                        .keep_min_output = {1, 0x00, {7}},
                        .stop_time = {1, 0x07},
                        .critical_temp = {1, 0x35},
                    },
                    .speed_cruise = {
                        .target_speed_count_low = {1, 0x01},
                        .target_speed_count_high = {1, 0x0C, {3, 0}},
                        .tolerance_low = {1, 0x02, {2, 0}},
                        .tolerance_high = {1, 0x0C, {6, 4}},
                        .step_up_value = {1, 0x66, {7, 4}},
                        .step_down_value = {1, 0x66, {3, 0}},
                    },
                    .step_up_time = {1, 0x03},
                    .step_down_time = {1, 0x04},
                },
                .smart_fan4 = {.available = true,
                    .control_points = {
                        {{1, 0x21}, {1, 0x27}},
                        {{1, 0x22}, {1, 0x28}},
                        {{1, 0x23}, {1, 0x29}},
                        {{1, 0x24}, {1, 0x2A}},
                    },
                },
            },
        },
        {
            .name = "CPUFAN",
            .rpm_high = {4, 0xC2}, .rpm_low = {4, 0xC3},
            .count = {4, 0xB2, /*bits=*/{}, /*next=*/{4, 0xB3, /*bits=*/{4, 0}}},
            .control = NuvotonFanControlInfo{
                .mode_select = {2, 0x02, {7, 4}},
                .output_value_write = {2, 0x09},
                .support_dc = false,
                .output_value_read = {0, 0x03},
                .temp_source = {2, 0x00, {4, 0}},
                .temp_value_int = {0, 0x75},
                .temp_value_frac = {0, 0x76, {7}},
                .smart_fan = {.available = true,
                    .thermal_cruise = {
                        .target_temp = {2, 0x01},
                        .tolerance = {2, 0x02, {2, 0}},
                        .start_value = {2, 0x06},
                        .stop_value = {2, 0x05},
                        .keep_min_output = {2, 0x00, {7}},
                        .stop_time = {2, 0x07},
                        .critical_temp = {2, 0x35},
                    },
                    .speed_cruise = {
                        .target_speed_count_low = {2, 0x01},
                        .target_speed_count_high = {2, 0x0C, {3, 0}},
                        .tolerance_low = {2, 0x02, {2, 0}},
                        .tolerance_high = {2, 0x0C, {6, 4}},
                        .step_up_value = {2, 0x66, {7, 4}},
                        .step_down_value = {2, 0x66, {3, 0}},
                    },
                    .step_up_time = {2, 0x03},
                    .step_down_time = {2, 0x04},
                },
                .smart_fan4 = {.available = true,
                    .control_points = {
                        {{2, 0x21}, {2, 0x27}},
                        {{2, 0x22}, {2, 0x28}},
                        {{2, 0x23}, {2, 0x29}},
                        {{2, 0x24}, {2, 0x2A}},
                    },
                },
            },
        },
    },
    // Temp sensors
    kNCT5532DTempSource,
    {
        {.name = "SMIOVT1", .val_int = {0, 0x27},
         .can_select = true, .select = {6, 0x21, {4, 0}}},
        {.name = "SMIOVT2", .val_int = {1, 0x50}, .val_frac = {0, 0x51, {7}},
         .can_select = true, .select = {6, 0x22, {4, 0}}},
        // It's weird that SYSTIN is present, but we can't read its
        // value directly. Indirectly we can use SMIOVT1 (default to
        // SYSTIN) to read it.
        // AUXTIN1 & AUXTIN2 also seem to be present.
        {.name = "CPUTIN", .val_int = {4, 0x91}, .offset = {4, 0x55},
            .sensor_type = {0, 0x5D, {2}}},
        {.name = "AUXTIN0", .val_int = {4, 0x92}, .offset = {4, 0x56},
            .sensor_type = {0, 0x5D, {3}}},
        {.name = "VTIN0", .val_int = {4, 0x95}, .offset = {4, 0x4C},
            .sensor_type = {0, 0x5D, {6}}},
        {"PCH_CPU_MAX", {4, 0x00}},
        {"PCH", {4, 0x01}},
        {"PCH_CPU", {4, 0x02}, {4, 0x03, {7, 2}}, true},
        {"MCH", {4, 0x04}},
        {"DIM0", {4, 0x05}},
        {"DIM1", {4, 0x06}},
        {"DIM2", {4, 0x07}},
        {"DIM3", {4, 0x08}},
        {"TSI0", {4, 0x09}, {4, 0x0A, {7, 5}}},
        {"TSI1", {4, 0x0B}, {4, 0x0C, {7, 5}}},
        {"TSI2", {4, 0x0D}, {4, 0x0E, {7, 5}}},
        {"TSI3", {4, 0x0F}, {4, 0x10, {7, 5}}},
        {"TSI4", {4, 0x11}, {4, 0x12, {7, 5}}},
        {"TSI5", {4, 0x13}, {4, 0x14, {7, 5}}},
        {"TSI6", {4, 0x15}, {4, 0x16, {7, 5}}},
        {"TSI7", {4, 0x17}, {4, 0x18, {7, 5}}},
        {"BYTE", {4, 0x19}, {4, 0x1A}},
    },
    // Volts
    {
        {"Vcore", {4, 0x80}},
        {"AVcc", {4, 0x82}, 2.0},
        {"3Vcc", {4, 0x83}, 2.0},
        {"Vin4", {4, 0x86}},
        {"3Vsb", {4, 0x87}, 2.0},
        {.name = "Vbat", .addr = {4, 0x88}, .enable = {0, 0x5D, {0}}},
        {"Vtt", {4, 0x89}},
        {"Vin2", {4, 0x8C}},
        {"Vin3", {4, 0x8D}},
    }
};

RegisterChip<NuvotonChipInfo> kRegisterNCT5532D(kNCT5532D);

}

