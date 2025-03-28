/*
 * nct6791d.cc
 * Copyright (C) 2025 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "nuvoton_chip_info.h"

namespace bsdsensors {

std::map<NuvotonTempSource, uint8_t> kNCT6791DTempSource{
        {NuvotonTempSource::kSourceSYSTIN, 1},
        {NuvotonTempSource::kSourceCPUTIN, 2},
        {NuvotonTempSource::kSourceAUXTIN0, 3},
        {NuvotonTempSource::kSourceAUXTIN1, 4},
        {NuvotonTempSource::kSourceAUXTIN2, 5},
        {NuvotonTempSource::kSourceAUXTIN3, 6},
        {NuvotonTempSource::kSourceSMBUSMASTER0, 8},
        {NuvotonTempSource::kSourceSMBUSMASTER1, 9},
        {NuvotonTempSource::kSourceSMBUSMASTER2, 10},
        {NuvotonTempSource::kSourceSMBUSMASTER3, 11},
        {NuvotonTempSource::kSourceSMBUSMASTER4, 12},
        {NuvotonTempSource::kSourceSMBUSMASTER5, 13},
        {NuvotonTempSource::kSourceSMBUSMASTER6, 14},
        {NuvotonTempSource::kSourceSMBUSMASTER7, 15},
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
        {NuvotonTempSource::kSourceVirtualTemp1, 31},
};

const NuvotonChipInfo kNCT6791D = {
    .device_id_to_name = {{0xC800, "NCT6791D"}},
    .vendor_id_addr = {0, 0x4F},
    // Fan speed info
    .fans = {
        {
            .name = "SYSFAN",
            .rpm_high = {4, 0xC0},
            .rpm_low = {4, 0xC1},
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
                        // unit is 50RPM, unless RPM High mode (100RPM)
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
            .rpm_high = {4, 0xC2},
            .rpm_low = {4, 0xC3},
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
        {
            .name = "AUXFAN0",
            .rpm_high = {4, 0xC4},
            .rpm_low = {4, 0xC5},
            .count = {4, 0xB4, /*bits=*/{}, /*next=*/{4, 0xB5, /*bits=*/{4, 0}}},
            .control = NuvotonFanControlInfo{
                .mode_select = {3, 0x02, {7, 4}},
                .output_value_write = {3, 0x09},
                .support_dc = false,
                .output_value_read = {0, 0x11},
                .temp_source = {3, 0x00, {4, 0}},
                .temp_value_int = {0, 0x77},
                .temp_value_frac = {0, 0x78, {7}},
                .smart_fan = {.available = true,
                    .thermal_cruise = {
                        .target_temp = {3, 0x01},
                        .tolerance = {3, 0x02, {2, 0}},
                        .start_value = {3, 0x06},
                        .stop_value = {3, 0x05},
                        .keep_min_output = {3, 0x00, {7}},
                        .stop_time = {3, 0x07},
                        .critical_temp = {3, 0x35},
                    },
                    .speed_cruise = {
                        .target_speed_count_low = {3, 0x01},
                        .target_speed_count_high = {3, 0x0C, {3, 0}},
                        .tolerance_low = {3, 0x02, {2, 0}},
                        .tolerance_high = {3, 0x0C, {6, 4}},
                        .step_up_value = {3, 0x66, {7, 4}},
                        .step_down_value = {3, 0x66, {3, 0}},
                    },
                    .step_up_time = {3, 0x03},
                    .step_down_time = {3, 0x04},
                },
                .smart_fan4 = {.available = true,
                    .control_points = {
                        {{3, 0x21}, {3, 0x27}},
                        {{3, 0x22}, {3, 0x28}},
                        {{3, 0x23}, {3, 0x29}},
                        {{3, 0x24}, {3, 0x2A}},
                    },
                },
            },
        },
        {
            .name = "AUXFAN1",
            .rpm_high = {4, 0xC6},
            .rpm_low = {4, 0xC7},
            .count = {4, 0xB6, /*bits=*/{}, /*next=*/{4, 0xB7, /*bits=*/{4, 0}}},
            .control = NuvotonFanControlInfo{
                .mode_select = {8, 0x02, {7, 4}},
                .output_value_write = {8, 0x09},
                .support_dc = false,
                .output_value_read = {0, 0x13},
                .temp_source = {8, 0x00, {4, 0}},
                .temp_value_int = {0, 0x79},
                .temp_value_frac = {0, 0x7A, {7}},
                .smart_fan = {.available = true,
                    .thermal_cruise = {
                        .target_temp = {8, 0x01},
                        .tolerance = {8, 0x02, {2, 0}},
                        .start_value = {8, 0x06},
                        .stop_value = {8, 0x05},
                        .keep_min_output = {8, 0x00, {7}},
                        .stop_time = {8, 0x07},
                        .critical_temp = {8, 0x35},
                    },
                    .speed_cruise = {
                        .target_speed_count_low = {8, 0x01},
                        .target_speed_count_high = {8, 0x0C, {3, 0}},
                        .tolerance_low = {8, 0x02, {2, 0}},
                        .tolerance_high = {8, 0x0C, {6, 4}},
                        .step_up_value = {8, 0x66, {7, 4}},
                        .step_down_value = {8, 0x66, {3, 0}},
                    },
                    .step_up_time = {8, 0x03},
                    .step_down_time = {8, 0x04},
                },
                .smart_fan4 = {.available = true,
                    .control_points = {
                        {{8, 0x21}, {8, 0x27}},
                        {{8, 0x22}, {8, 0x28}},
                        {{8, 0x23}, {8, 0x29}},
                        {{8, 0x24}, {8, 0x2A}},
                    },
                },
            },
        },
        {
            .name = "AUXFAN2",
            .rpm_high = {4, 0xC8},
            .rpm_low = {4, 0xC9},
            .count = {4, 0xB8, /*bits=*/{}, /*next=*/{4, 0xB9, /*bits=*/{4, 0}}},
            .control = NuvotonFanControlInfo{
                .mode_select = {9, 0x02, {7, 4}},
                .output_value_write = {9, 0x09},
                .support_dc = false,
                .output_value_read = {0, 0x15},
                .temp_source = {9, 0x00, {4, 0}},
                .temp_value_int = {0, 0x7B},
                .temp_value_frac = {0, 0x7C, {7}},
                .smart_fan = {.available = true,
                    .thermal_cruise = {
                        .target_temp = {9, 0x01},
                        .tolerance = {9, 0x02, {2, 0}},
                        .start_value = {9, 0x06},
                        .stop_value = {9, 0x05},
                        .keep_min_output = {9, 0x00, {7}},
                        .stop_time = {9, 0x07},
                        .critical_temp = {9, 0x35},
                    },
                    .speed_cruise = {
                        .target_speed_count_low = {9, 0x01},
                        .target_speed_count_high = {9, 0x0C, {3, 0}},
                        .tolerance_low = {9, 0x02, {2, 0}},
                        .tolerance_high = {9, 0x0C, {6, 4}},
                        .step_up_value = {9, 0x66, {7, 4}},
                        .step_down_value = {9, 0x66, {3, 0}},
                    },
                    .step_up_time = {9, 0x03},
                    .step_down_time = {9, 0x04},
                },
                .smart_fan4 = {.available = true,
                    .control_points = {
                        {{9, 0x21}, {9, 0x27}},
                        {{9, 0x22}, {9, 0x28}},
                        {{9, 0x23}, {9, 0x29}},
                        {{9, 0x24}, {9, 0x2A}},
                    },
                },
            },
        },
    },
    // Temp sensors
    .temp_table = kNCT6791DTempSource,
    .temps = {
        {.name = "SMIOVT1", .val_int = {0, 0x27},
         .can_select = true, .select = {6, 0x21, {4, 0}}},
        {.name = "SMIOVT2", .val_int = {1, 0x50}, .val_frac = {0, 0x51, {7}},
         .can_select = true, .select = {6, 0x22, {4, 0}}},
        {.name = "SYSTIN", .val_int = {4, 0x90}, .offset = {4, 0x54},
            .sensor_type = {0, 0x5D, {1}}},
        {.name = "CPUTIN", .val_int = {4, 0x91}, .offset = {4, 0x55},
            .sensor_type = {0, 0x5D, {2}}},
        {.name = "AUXTIN0", .val_int = {4, 0x92}, .offset = {4, 0x56},
            .sensor_type = {0, 0x5D, {3}}},
        {.name = "AUXTIN1", .val_int = {4, 0x93}, .offset = {4, 0x4A},
            .sensor_type = {0, 0x5D, {4}}},
        {.name = "AUXTIN2", .val_int = {4, 0x94}, .offset = {4, 0x4B},
            .sensor_type = {0, 0x5D, {5}}},
        {.name = "AUXTIN3", .val_int = {4, 0x95}, .offset = {4, 0x4C},
            .sensor_type = {0, 0x5D, {6}}},
        {"PECI0Calibration", {4, 0xF4}},
        {"PECI1Calibration", {4, 0xF5}},
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
        {"VSYSFAN", {0, 0xEA}},
        {"VCPUFAN", {0, 0xEB}},
        {"VAUXFAN0", {0, 0xEC}},
        {"VAUXFAN1", {0, 0xED}},
        {"VAUXFAN2", {0, 0xEE}},
    },
    // Volts
    .volts = {
        {"Vcore", {4, 0x80}},
        {"Vin1", {4, 0x81}},
        {"AVcc", {4, 0x82}, 2.0},
        {"3Vcc", {4, 0x83}, 2.0},
        {"Vin0", {4, 0x84}},
        {"Vin8", {4, 0x85}},
        {"Vin4", {4, 0x86}},
        {"3Vsb", {4, 0x87}, 2.0},
        {.name = "Vbat", .addr = {4, 0x88}, .enable = {0, 0x5D, {0}}},
        {"Vtt", {4, 0x89}},
        {"Vin5", {4, 0x8A}},
        {"Vin6", {4, 0x8B}},
        {"Vin2", {4, 0x8C}},
        {"Vin3", {4, 0x8D}},
        {"Vin7", {4, 0x8E}},
    },
    .io_space_enable = 0x28,
};

RegisterChip<NuvotonChipInfo> kRegisterNCT6791D(kNCT6791D);

}

