/*
 * w83667hg.cc
 * Copyright (C) 2025 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "nuvoton_chip_info.h"

namespace bsdsensors {

std::map<NuvotonTempSource, uint8_t> kW83667HGTempSource{
        {NuvotonTempSource::kSourceSYSTIN, 0},
        {NuvotonTempSource::kSourceCPUTIN, 1},
        {NuvotonTempSource::kSourceAUXTIN0, 2},
        {NuvotonTempSource::kSourceAMDTSI, 3},
        {NuvotonTempSource::kSourcePECI0, 4},
        {NuvotonTempSource::kSourcePECI1, 5},
        {NuvotonTempSource::kSourcePECI2, 6},
        {NuvotonTempSource::kSourcePECI3, 7},
};

const NuvotonChipInfo kW83667HG = {
    .device_id_to_name = {
        {0xA513, "W83667HG"},
    },
    .vendor_id_addr = {0, 0x4F},
    .fans = {
        {
            .name = "SYSFAN",
            .count = {0, 0x28}, .divisor = {0, 0x5D, {5}, {0, 0x47, {5, 4}}},
            .control = NuvotonFanControlInfo{
                .mode_select = {0, 0x04, {3, 2}},
                .output_value_write = {0, 0x01},
                .output_value_write_dc = {0, 0x01, {7, 2}},
                .support_dc = true,
                .output_type = {0, 0x04, {0}},
                .output_value_read = {0, 0x01},
                .temp_source = {0, 0x4A, {7, 5}},
                .temp_value_int = {0, 0x27},
                .temp_value_frac = {0, 0x7C, {7}},
                .smart_fan = {.available = true,
                    .thermal_cruise = {
                        .target_temp = {0, 0x05},
                        .tolerance = {0, 0x07, {3, 0}},
                        .start_value = {0, 0x0A},
                        .stop_value = {0, 0x08},
                        .keep_min_output = {0, 0x12, {5}},
                        .stop_time = {0, 0x0C},
                        .critical_temp = {0, 0x75},
                    },
                    .speed_cruise = {
                        .target_speed_count_low = {0, 0x05},
                        .tolerance_low = {0, 0x07, {3, 0}},
                        .keep_min_output = {0, 0x12, {5}},
                    },
                    .step_up_time = {0, 0x0F},
                    .step_down_time = {0, 0x0E},
                },
            },
        },
        {
            .name = "CPUFAN",
            .count = {0, 0x29}, .divisor = {0, 0x5D, {6}, {0, 0x47, {7, 6}}},
            .control = NuvotonFanControlInfo{
                .mode_select = {0, 0x04, {5, 4}},
                .output_value_write = {0, 0x03},
                .output_value_write_dc = {0, 0x03, {7, 2}},
                .support_dc = true,
                .output_type = {0, 0x04, {1}},
                .output_value_read = {0, 0x03},
                .temp_source = {0, 0x49, {2, 0}},
                .temp_value_int = {1, 0x50},
                .temp_value_frac = {1, 0x51, {7}},
                .smart_fan = {.available = true,
                    .thermal_cruise = {
                        .target_temp = {0, 0x06},
                        .tolerance = {0, 0x07, {7, 4}},
                        .start_value = {0, 0x0B},
                        .stop_value = {0, 0x09},
                        .keep_min_output = {0, 0x12, {4}},
                        .stop_time = {0, 0x0D},
                        .critical_temp = {0, 0x76},
                    },
                    .speed_cruise = {
                        .target_speed_count_low = {0, 0x06},
                        .tolerance_low = {0, 0x07, {7, 4}},
                        .keep_min_output = {0, 0x12, {4}},
                    },
                    .step_up_time = {0, 0x71},
                    .step_down_time = {0, 0x70},
                },
            },
        },
        {
            .name = "AUXFAN",
            .count = {0, 0x2A}, .divisor = {0, 0x5D, {7}, {0, 0x4B, {7, 6}}},
            .control = NuvotonFanControlInfo{
                .mode_select = {0, 0x12, {2, 1}},
                .output_value_write = {0, 0x11},
                .output_value_write_dc = {0, 0x11, {7, 2}},
                .support_dc = true,
                .output_type = {0, 0x12, {0}},
                .output_value_read = {0, 0x11},
                .temp_source = {0, 0x49, {6, 4}},
                .temp_value_int = {2, 0x50},
                .temp_value_frac = {2, 0x51, {7}},
                .smart_fan = {.available = true,
                    .thermal_cruise = {
                        .target_temp = {0, 0x13},
                        .tolerance = {0, 0x14, {3, 0}},
                        .start_value = {0, 0x16},
                        .stop_value = {0, 0x15},
                        .keep_min_output = {0, 0x12, {3}},
                        .stop_time = {0, 0x17},
                        .critical_temp = {0, 0x77},
                    },
                    .speed_cruise = {
                        .target_speed_count_low = {0, 0x13},
                        .tolerance_low = {0, 0x14, {3, 0}},
                        .keep_min_output = {0, 0x12, {3}},
                    },
                    .step_up_time = {0, 0x73},
                    .step_down_time = {0, 0x72},
                },
            },
        },
        {
            .name = "AUXFAN1",
            .count = {0, 0x3F}, .divisor = {0, 0x4C, {7}, {0, 0x59, {1, 0}}},
        },
        {
            .name = "AUXFAN2",
            .count = {5, 0x53}, .divisor = {0, 0x59, {7, 7, {3, 2}}},
        },
    },
    .temp_table = kW83667HGTempSource,
    .temps = {
        {.name = "TEMP", .val_int = {0, 0x7E},
            .can_select = true, .select = {0, 0x7D, {2, 0}}},
        {.name = "SYSTIN", .val_int = {0, 0x27},
            .offset = {4, 0x54}, .sensor_type = {0, 0x5D, {1}}},
        {.name = "CPUTIN", .val_int = {1, 0x50}, .val_frac = {1, 0x51, {7}},
            .offset = {4, 0x55}, .sensor_type = {0, 0x5D, {2}}},
        {.name = "AUXTIN", .val_int = {2, 0x50}, .val_frac = {2, 0x51, {7}},
            .offset = {4, 0x56}, .sensor_type = {0, 0x5D, {3}}},
    },
    .volts = {
        {"Vcore", {0, 0x20}},
        {"Vin0", {0, 0x21}},
        {"AVcc", {0, 0x22}, 2.0},
        {"3Vcc", {0, 0x23}, 2.0},
        {"Vin1", {0, 0x24}},
        {"Vcore_refin", {0, 0x25}},
        {"Vin2", {0, 0x26}},
        {"3Vsb", {5, 0x50}, 2.0},
        {.name = "Vbat", .addr = {5, 0x51}, .enable = {0, 0x5D, {0}}},
    },
    .notes = "Note: SYSTIN, CPUTIN, and AUXTIN are actually temp sensors selected"
        " for SYSFAN, CPUFAN, and AUXFAN. Thus, only in the default setting, they"
        " represent the corresponding temp sensors. If these FANs are using other"
        " temp sensors as their temp source, then using the selectable TEMP sensor"
        " would be the option to get real sensor values."
};

RegisterChip<NuvotonChipInfo> kRegisterW83667HG(kW83667HG);

}

