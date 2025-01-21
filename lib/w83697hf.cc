/*
 * w83697hf.cc
 * Copyright (C) 2025 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "nuvoton_chip_info.h"
#include "nuvoton_temp_sensor.h"

namespace bsdsensors {

// No temp source can be changed.
std::map<NuvotonTempSource, uint8_t> kW83697HFTempSource{};

const NuvotonChipInfo kW83697HF = {
    .device_id_to_name = {
        // Actually it covers 1X, X = revision
        {0x6015, "W83697HF"},
    },
    .vendor_id_addr = {0, 0x4F},
    .fans = {
        {
            .name = "FAN1",
            .count = {0, 0x28},
            .divisor = {0, 0x5D, {5}, {0, 0x47, {5, 4}}},
            .control = NuvotonFanControlInfo{
                .mode_select = {0, 0x04, {3, 2}},
                .output_value_write = {0, 0x01},
                .smart_fan = { .available = true,
                    .thermal_cruise = {
                        .target_temp = {0, 0x05, {6, 0}},
                        .tolerance = {0, 0x07, {3, 0}},
                        .start_value = {0, 0x0A},
                        .stop_value = {0, 0x08},
                        // unit is 0.1s
                        .stop_time = {0, 0x0C},
                        .step_up_time = {0, 0x0F},
                        .step_down_time = {0, 0x0E},
                    },
                    .speed_cruise = {
                        .target_speed_count_low = {0, 0x05},
                        .tolerance_low = {0, 0x07, {3, 0}},
                        .step_up_time = {0, 0x0F},
                        .step_down_time = {0, 0x0E},
                    }
                },
                // Actually it's VTIN1
                .fixed_temp_source = NuvotonTempSource::kSourceCPUTIN,
            },
        },
        {
            .name = "FAN2",
            .count = {0, 0x29},
            .divisor = {0, 0x5D, {6}, {0, 0x47, {7, 6}}},
            .control = NuvotonFanControlInfo{
                .mode_select = {0, 0x04, {5, 4}},
                .output_value_write = {0, 0x03},
                .smart_fan = { .available = true,
                    .thermal_cruise = {
                        .target_temp = {0, 0x06, {6, 0}},
                        .tolerance = {0, 0x07, {7, 4}},
                        .start_value = {0, 0x0B},
                        .stop_value = {0, 0x09},
                        // unit is 0.1s
                        .stop_time = {0, 0x0D},
                        .step_up_time = {0, 0x0F},
                        .step_down_time = {0, 0x0E},
                    },
                    .speed_cruise = {
                        .target_speed_count_low = {0, 0x06},
                        .tolerance_low = {0, 0x07, {7, 4}},
                        .step_up_time = {0, 0x0F},
                        .step_down_time = {0, 0x0E},
                    }
                },
                // Actually it's VTIN2
                .fixed_temp_source = NuvotonTempSource::kSourceSYSTIN,
            },
        },
    },
    .temp_table = kW83697HFTempSource,
    .temps = {
        {.name = "VTIN1", .val_int = {0, 0x27},
         .offset = {4, 0x54}, .sensor_type = {0, 0x5D, {1}}},
        {.name = "VTIN2", .val_int = {1, 0x50}, .val_frac = {1, 0x51, {7}},
         .offset = {4, 0x55}, .sensor_type = {0, 0x5D, {2}}},
    },
    .volts = {
        // It's not clear how the motherboard will wire external resistors.
        // So these scaling numbers might be wrong.
        {"VcoreA", {0, 0x20}},
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
    .notes = "",
    // This chip has a range of 0~4V, so 1 unit = 16mV.
    .volt_unit = 0.016,
};

RegisterChip<NuvotonChipInfo> kRegisterW83697HF(kW83697HF);

}

