/*
 * w83627hgaw.cc
 * Copyright (C) 2025 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "nuvoton_chip_info.h"
#include "nuvoton_temp_sensor.h"

namespace bsdsensors {

// No temp source can be changed.
std::map<NuvotonTempSource, uint8_t> kW83627HGAWTempSource{};

const NuvotonChipInfo kW83627HGAW = {
    .device_id_to_name = {
        {0x5217, "W83627HG-AW, rev. G"},
        {0x523A, "W83627HG-AW, rev. J"},
        {0x5241, "W83627HG-AW, rev. UD-A"},
    },
    .vendor_id_addr = {0, 0x4F},
    .fans = {
        {
            .name = "FAN1",
            .count = {0, 0x28},
            .divisor = {0, 0x5D, {5}, {0, 0x47, {5, 4}}},
            .control = NuvotonFanControlInfo{
                .output_value_write = {0, 0x5A},
            },
        },
        {
            .name = "FAN2",
            .count = {0, 0x29},
            .divisor = {0, 0x5D, {6}, {0, 0x47, {7, 6}}},
            .control = NuvotonFanControlInfo{
                .output_value_write = {0, 0x5B},
            },
        },
        {
            .name = "FAN3",
            .count = {0, 0x2A},
            .divisor = {0, 0x5D, {7}, {0, 0x4B, {7, 6}}},
            .control = NuvotonFanControlInfo{
                .output_value_write = {0, 0x11},
            },
        },
    },
    .temp_table = kW83627HGAWTempSource,
    .temps = {
        {.name = "VTIN1", .val_int = {0, 0x27}, .offset = {4, 0x54},
         .sensor_type = {0, 0x5D, {1}}},
        {.name = "VTIN2", .val_int = {1, 0x50}, .val_frac = {1, 0x51, {7}},
         .offset = {4, 0x55}, .sensor_type = {0, 0x5D, {2}}},
        {.name = "VTIN3", .val_int = {2, 0x50}, .val_frac = {2, 0x51, {7}},
         .offset = {4, 0x56}, .sensor_type = {0, 0x5D, {3}}},
    },
    .volts = {
        // It's not clear how the motherboard will wire external resistors.
        // So these scaling numbers might be wrong.
        {"VcoreA", {0, 0x20}},
        {"VcoreB", {0, 0x21}},
        {"3.3Vin", {0, 0x22}},
        // Based on the datasheet, 5V might be converted to 0~4V with 50/(50+34)
        {"5Vin", {0, 0x23}, (50.0+34.0)/50.0},
        {"12Vin", {0, 0x24}, (10.0+28.0)/10.0},
        // Use 232K and 56K resistors, 0.567V -> -12V
        {"-12Vin", {0, 0x25}, 5.14, -14.91},
        // Use 120K and 56K resistors, 0.8635V -> -5V
        {"-5Vin", {0, 0x26}, 3.14, -7.71},
        {"5Vsb", {5, 0x50}, (50.0+34.0)/50.0},
        {.name = "Vbat", .addr = {5, 0x51}, .enable = {0, 0x5D, {0}}},
    },
    .notes = "Note: no smart fan support at all, only manual.",
    // This chip has a range of 0~4V, so 1 unit = 16mV.
    .volt_unit = 0.016,
};

RegisterChip<NuvotonChipInfo> kRegisterW83627HGAW(kW83627HGAW);

}
