/*
 * it8772.cc
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "ite_chip_info.h"

namespace bsdsensors {

ITEChipInfo kIT8772{
    .device_id_to_name = {{0x8772, "IT8772"}},
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
        {.name = "3Vsb", .value = 0x27, .alpha = 2.0},
        {.name = "VBAT", .value = 0x28},
    },
};

RegisterChip<ITEChipInfo> kRegisterIT8772(kIT8772);

}  // namespace bsdsensors
