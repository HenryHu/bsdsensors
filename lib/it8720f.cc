/*
 * it8720f.cc
 * Copyright (C) 2025 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "ite_chip_info.h"

namespace bsdsensors {

std::map<uint8_t, std::string> kIT8720FTempSource = {
    {0b00, "TMPIN1"},
    {0b01, "TMPIN2"},
    {0b10, "TMPIN3"},
};

ITEChipInfo kIT8720F{
    .device_id_to_name = {{0x8720, "IT8720F"}},
    .temps = {
        {.name = "TMPIN1", .value = 0x29},
        {.name = "TMPIN2", .value = 0x2A},
        {.name = "TMPIN3", .value = 0x2B},
    },
    .volts = {
        {.name = "VIN0", .value = 0x20},
        {.name = "VIN1", .value = 0x21},
        {.name = "VIN2", .value = 0x22},
        {.name = "VIN3", .value = 0x23},
        {.name = "VIN4", .value = 0x24},
        {.name = "VIN5", .value = 0x25},
        {.name = "VIN6", .value = 0x26},
        {.name = "VIN7", .value = 0x27},
        {.name = "VBAT", .value = 0x28},
    },
    .fan_speeds = {
        {.name = "FAN1", .count = 0x0D, .count_high = 0x18, .wide_mode = {0x0C, {0}},
            .enable = {0x13, {4}}, .output_mode = {0x13, {0}}},
        {.name = "FAN2", .count = 0x0E, .count_high = 0x19, .wide_mode = {0x0C, {1}},
            .enable = {0x13, {5}}, .output_mode = {0x13, {1}}},
        {.name = "FAN3", .count = 0x0F, .count_high = 0x1A, .wide_mode = {0x0C, {2}},
            .enable = {0x13, {6}}, .output_mode = {0x13, {2}}},
        {.name = "FAN4", .count = 0x80, .count_high = 0x81, .enable = {0x0C, {4}}},
        {.name = "FAN5", .count = 0x82, .count_high = 0x82, .enable = {0x0C, {5}}},
    },
    .fan_controls = {
        {
            .name = "FAN_CTL1",
            .mode_select = {0x15, {7}},
            .pwm = {0x15, {6, 0}},
            .temp_input_select = {0x15, {1, 0}},
            .temp_inputs = kIT8720FTempSource,
        },
        {
            .name = "FAN_CTL2",
            .mode_select = {0x16, {7}},
            .pwm = {0x16, {6, 0}},
            .temp_input_select = {0x16, {1, 0}},
            .temp_inputs = kIT8720FTempSource,
        },
        {
            .name = "FAN_CTL3",
            .mode_select = {0x17, {7}},
            .pwm = {0x17, {6, 0}},
            .temp_input_select = {0x17, {1, 0}},
            .temp_inputs = kIT8720FTempSource,
        },
    },
};

RegisterChip<ITEChipInfo> kRegisterIT8720F(kIT8720F);

}  // namespace bsdsensors
