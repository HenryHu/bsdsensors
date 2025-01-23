/*
 * w83627thf.cc
 * Copyright (C) 2025 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "nuvoton_chip_info.h"
#include "nuvoton_temp_sensor.h"

namespace bsdsensors {

std::map<NuvotonTempSource, uint8_t> kW83627THFTempSource{
};

const NuvotonChipInfo kW83627THF= {
    .device_id_to_name = {{0x8283, "W83627THF"}},
    .vendor_id_addr = {0, 0x4F},
    .fans = {
        {
            .name = "SYSFAN",
            .count = {0, 0x28},
            .divisor = {0, 0x5D, {5}, {0, 0x47, {5, 4}}},
            .control = NuvotonFanControlInfo{
                .mode_select = {0, 0x04, {3, 2}},
                // Output voltage = AVcc * {7, 4} / 16
                // It's {7,4}, 1/16, which is the same as {7, 2}, 1/64.
                .output_value_write_dc = {0, 0x01, {7, 2}},
                .support_dc = true,
                .smart_fan = {.available = true,
                    .thermal_cruise = {
                        .target_temp = {0, 0x05, {6, 0}},
                        .tolerance = {0, 0x07, {3, 0}},
                        .start_value = {0, 0x0A},
                        .stop_value = {0, 0x08},
                        .keep_min_output = {0, 0x12, {5}},
                        // unit is 0.1s
                        .stop_time = {0, 0x0C},
                    },
                    .speed_cruise = {
                        .target_speed_count_low = {0, 0x05},
                        .tolerance_low = {0, 0x07, {3, 0}},
                        .keep_min_output = {0, 0x12, {5}},
                    },
                    // unit is 1.6s
                    .step_up_time = {0, 0x0F},
                    .step_down_time = {0, 0x0E},
                },
                .fixed_temp_source = NuvotonTempSource::kSourceSYSTIN,
            },
        },
        {
            .name = "CPUFA",
            .count = {0, 0x29},
            .divisor = {0, 0x5D, {6}, {0, 0x47, {7, 6}}},
            .control = NuvotonFanControlInfo{
                .mode_select = {0, 0x04, {5, 4}},
                .output_value_write_dc = {0, 0x03, {7, 2}},
                .support_dc = true,
                .smart_fan = {.available = true,
                    .thermal_cruise = {
                        .target_temp = {0, 0x06, {6, 0}},
                        .tolerance = {0, 0x07, {7, 4}},
                        .start_value = {0, 0x0B},
                        .stop_value = {0, 0x09},
                        .keep_min_output = {0, 0x12, {4}},
                        // unit is 0.1s
                        .stop_time = {0, 0x0D},
                    },
                    .speed_cruise = {
                        .target_speed_count_low = {0, 0x06},
                        .tolerance_low = {0, 0x07, {7, 4}},
                        .keep_min_output = {0, 0x12, {4}},
                    },
                    // unit is 1.6s
                    .step_up_time = {0, 0x0F},
                    .step_down_time = {0, 0x0E},
                },
                .fixed_temp_source = NuvotonTempSource::kSourceCPUTIN,
            },
        },
        {
            .name = "AUXFAN",
            .count = {0, 0x2A},
            .divisor = {0, 0x5D, {7}, {0, 0x4B, {7, 6}}},
            .control = NuvotonFanControlInfo{
                .mode_select = {0, 0x12, {2, 1}},
                .output_value_write = {0, 0x11},
                // voltage = AVcc * value / 64
                .output_value_write_dc = {0, 0x11, {7, 2}},
                .support_dc = true,
                .smart_fan = {.available = true,
                    .thermal_cruise = {
                        .target_temp = {0, 0x13, {6, 0}},
                        .tolerance = {0, 0x14, {3, 0}},
                        .start_value = {0, 0x16},
                        .stop_value = {0, 0x15},
                        .keep_min_output = {0, 0x12, {3}},
                        // unit is 0.1s
                        .stop_time = {0, 0x17},
                    },
                    .speed_cruise = {
                        .target_speed_count_low = {0, 0x13},
                        .tolerance_low = {0, 0x14, {3, 0}},
                        .keep_min_output = {0, 0x12, {3}},
                    },
                    .step_up_time = {0, 0x0F},
                    .step_down_time = {0, 0x0E},
                },
                .fixed_temp_source = NuvotonTempSource::kSourceAUXTIN0,
            },
        },
    },
    .temp_table = kW83627THFTempSource,
    .temps = {
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
        {"Vin1", {0, 0x22}},
        {"AVcc", {0, 0x23}, 2.0},
        {"Vin2", {0, 0x24}},
        // This is wrong (range is 0~4V), but we don't know the right scale.
        {"5Vsb", {5, 0x50}},
        {.name = "Vbat", .addr = {5, 0x51}, .enable = {0, 0x5D, {0}}},
    },
    .notes = "Note: does not seem to support PWM. No changeable temp source or fan control temp source.",
    .volt_unit = 0.016,
};

RegisterChip<NuvotonChipInfo> kRegisterW83627THF(kW83627THF);

}



