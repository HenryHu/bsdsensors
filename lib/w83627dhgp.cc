/*
 * w83627dhgp.cc
 * Copyright (C) 2025 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "nuvoton_chip_info.h"
#include "nuvoton_temp_sensor.h"

namespace bsdsensors {

std::map<NuvotonTempSource, uint8_t> kW83627DHGPTempSource{
    {NuvotonTempSource::kSourceSYSTIN, 0},
    {NuvotonTempSource::kSourceCPUTIN, 1},
    {NuvotonTempSource::kSourceAUXTIN0, 2},
    {NuvotonTempSource::kSourcePECI0, 4},
    {NuvotonTempSource::kSourcePECI1, 5},
    {NuvotonTempSource::kSourcePECI2, 6},
    {NuvotonTempSource::kSourcePECI3, 7},
};

const NuvotonChipInfo kW83627DHGP = {
    .device_id_to_name = {{0xB070, "W83627DHG-P/DHG-PT"}},
    .vendor_id_addr = {0, 0x4F},
    .fans = {
        {
            .name = "SYSFAN",
            .rpm_high = {6, 0x50},
            .rpm_low = {6, 0x51},
            .count = {0, 0x28},
            .divisor = {0, 0x5D, {5}, {0, 0x47, {5, 4}}},
            .control = NuvotonFanControlInfo{
                .mode_select = {0, 0x04, {3, 2}},
                .output_value_write = {0, 0x01},
                .output_value_write_dc = {0, 0x01, {7, 2}},
                .support_dc = true,
                .output_type = {0, 0x04, {0}},
                .output_value_read = {0, 0x01},
                .smart_fan = {.available = true,
                    .thermal_cruise = {
                        .target_temp = {0, 0x05, {6, 0}},
                        .tolerance = {0, 0x07, {3, 0}},
                        .start_value = {0, 0x0A},
                        .stop_value = {0, 0x08},
                        .keep_min_output = {0, 0x12, {5}},
                        // PWM - unit is 0.1s; DC - unit is 0.4s
                        .stop_time = {0, 0x0C},
                        .critical_temp = {0, 0x6B},
                    },
                    .speed_cruise = {
                        .target_speed_count_low = {0, 0x05},
                        .tolerance_low = {0, 0x07, {3, 0}},
                        .keep_min_output = {0, 0x12, {5}},
                    },
                    .step_up_time = {0, 0x0F},
                    .step_down_time = {0, 0x0E},
                },
                .fixed_temp_source = NuvotonTempSource::kSourceSYSTIN,
            },
        },
        {
            .name = "CPUFAN0",
            .rpm_high = {6, 0x52},
            .rpm_low = {6, 0x53},
            .count = {0, 0x29},
            .divisor = {0, 0x5D, {6}, {0, 0x47, {7, 6}}},
            .control = NuvotonFanControlInfo{
                .mode_select = {0, 0x04, {5, 4}},
                .output_value_write = {0, 0x03},
                .output_value_write_dc = {0, 0x03, {7, 2}},
                .support_dc = true,
                .output_type = {0, 0x04, {1}},
                .output_value_read = {0, 0x03},
                .temp_source = {0, 0x49, {2, 0}},
                .smart_fan = {.available = true,
                    .thermal_cruise = {
                        .target_temp = {0, 0x06, {6, 0}},
                        .tolerance = {0, 0x07, {7, 4}},
                        .start_value = {0, 0x0B},
                        .stop_value = {0, 0x09},
                        .keep_min_output = {0, 0x12, {4}},
                        // PWM - unit is 0.1s; DC - unit is 0.4s
                        .stop_time = {0, 0x0D},
                        .critical_temp = {0, 0x6C},
                    },
                    .speed_cruise = {
                        .target_speed_count_low = {0, 0x06},
                        .tolerance_low = {0, 0x07, {7, 4}},
                        .keep_min_output = {0, 0x12, {4}},
                    },
                    .step_up_time = {0, 0x0F},
                    .step_down_time = {0, 0x0E},
                },
                .source_select = {
                    {0, NuvotonTempSource::kSourceCPUTIN},
                    {2, NuvotonTempSource::kSourcePECI0},
                    {3, NuvotonTempSource::kSourcePECI1},
                    {4, NuvotonTempSource::kSourcePECI2},
                    {5, NuvotonTempSource::kSourcePECI3},
                },
            },
        },
        {
            .name = "AUXFAN0",
            .rpm_high = {6, 0x54},
            .rpm_low = {6, 0x55},
            .count = {0, 0x2A},
            .divisor = {0, 0x5D, {7}, {0, 0x4B, {7, 6}}},
            .control = NuvotonFanControlInfo{
                .mode_select = {0, 0x12, {2, 1}},
                .output_value_write = {0, 0x11},
                // voltage = AVcc * value / 64
                .output_value_write_dc = {0, 0x11, {7, 2}},
                .support_dc = true,
                .output_type = {0, 0x12, {0}},
                .output_value_read = {0, 0x11},
                .temp_source = {0, 0x49, {6, 4}},
                .smart_fan = {.available = true,
                    .thermal_cruise = {
                        .target_temp = {0, 0x13, {6, 0}},
                        .tolerance = {0, 0x14, {3, 0}},
                        .start_value = {0, 0x16},
                        .stop_value = {0, 0x15},
                        .keep_min_output = {0, 0x12, {3}},
                        // PWM - unit is 0.1s; DC - unit is 0.4s
                        .stop_time = {0, 0x17},
                        .critical_temp = {0, 0x6D},
                    },
                    .speed_cruise = {
                        .target_speed_count_low = {0, 0x13},
                        .tolerance_low = {0, 0x14, {3, 0}},
                        .keep_min_output = {0, 0x12, {3}},
                    },
                    .step_up_time = {0, 0x0F},
                    .step_down_time = {0, 0x0E},
                },
                .source_select = {
                    {0, NuvotonTempSource::kSourceAUXTIN0},
                    {2, NuvotonTempSource::kSourcePECI0},
                    {3, NuvotonTempSource::kSourcePECI1},
                    {4, NuvotonTempSource::kSourcePECI2},
                    {5, NuvotonTempSource::kSourcePECI3},
                },
            },
        },
        {
            .name = "CPUFAN1",
            .rpm_high = {6, 0x56},
            .rpm_low = {6, 0x57},
            .count = {0, 0x3F},
            .divisor = {0, 0x4C, {7}, {0, 0x59, {1, 0}}},
            .control = NuvotonFanControlInfo{
                .mode_select = {0, 0x62, {5, 4}},
                .output_value_write = {0, 0x61},
                .output_value_write_dc = {0, 0x61, {7, 2}},
                .support_dc = true,
                .output_type = {0, 0x62, {6}},
                .output_value_read = {0, 0x61},
                .temp_source = {0, 0x4A, {7, 5}},
                .smart_fan = {.available = true,
                    .thermal_cruise = {
                        .target_temp = {0, 0x63, {6, 0}},
                        .tolerance = {0, 0x62, {3, 0}},
                        .start_value = {0, 0x65},
                        .stop_value = {0, 0x64},
                        .keep_min_output = {0, 0x12, {6}},
                        // PWM - unit is 0.1s; DC - unit is 0.4s
                        .stop_time = {0, 0x66},
                        .critical_temp = {0, 0x6E},
                    },
                    .speed_cruise = {
                        .target_speed_count_low = {0, 0x63},
                        .tolerance_low = {0, 0x62, {3, 0}},
                        .keep_min_output = {0, 0x12, {6}},
                    },
                    .step_up_time = {0, 0x0F},
                    .step_down_time = {0, 0x0E},
                },
                .source_select = {
                    {0, NuvotonTempSource::kSourceSYSTIN},
                    {1, NuvotonTempSource::kSourceCPUTIN},
                    {2, NuvotonTempSource::kSourceAUXTIN0},
                    {4, NuvotonTempSource::kSourcePECI0},
                    {5, NuvotonTempSource::kSourcePECI1},
                    {6, NuvotonTempSource::kSourcePECI2},
                    {7, NuvotonTempSource::kSourcePECI3},
                },
            },
        },
        {
            .name = "AUXFAN1",
            .rpm_high = {6, 0x58},
            .rpm_low = {6, 0x59},
            .count = {5, 0x53},
            .divisor = {0, 0x59, {7, 7, {3, 2}}},
        },
    },
    .temp_table = kW83627DHGPTempSource,
    .temps = {
        {.name = "TEMP", .val_int = {0, 0x7D}, .can_select = true,
            .select = {0, 0x7C, {2, 0}}},
        {.name = "SYSTIN", .val_int = {0, 0x27}, .offset = {4, 0x54}},
        {.name = "CPUTIN", .val_int = {1, 0x50}, .val_frac = {1, 0x51, {7}},
         .offset = {4, 0x55}},
        {.name = "AUXTIN", .val_int = {2, 0x50}, .val_frac = {2, 0x51, {7}},
         .offset = {4, 0x56}},
    },
    .volts = {
        {"Vcore", {0, 0x20}},
        {"Vin0", {0, 0x21}},
        {"AVcc", {0, 0x22}, 2.0},
        {"3Vcc", {0, 0x23}, 2.0},
        {"Vin1", {0, 0x24}},
        {"Vin2", {0, 0x25}},
        {"Vin3", {0, 0x26}},
        {"3Vsb", {5, 0x50}},
        {.name = "Vbat", .addr = {5, 0x51}, .enable = {0, 0x5D, {0}}},
    },
    .notes = "Note: all fans in speed-cruise and thermal-cruise modes share the same"
    "step-up and step-down time registers. "
    "Note: AUXFAN and SYSFAN does not support SmartFan3.",
};

RegisterChip<NuvotonChipInfo> kRegisterW83627DHGP(kW83627DHGP);

}

