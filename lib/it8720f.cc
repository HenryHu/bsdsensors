/*
 * it8720f.cc
 * Copyright (C) 2025 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "ite_chip_info.h"

namespace bsdsensors {

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
        {.name = "FAN1", .count = 0x0D},
        {.name = "FAN2", .count = 0x0E},
        {.name = "FAN3", .count = 0x0F},
    },
};

RegisterChip<ITEChipInfo> kRegisterIT8720F(kIT8720F);

}  // namespace bsdsensors
