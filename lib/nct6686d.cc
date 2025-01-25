/*
 * nct6686d.cc
 * Copyright (C) 2025 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "nuvoton_chip_info.h"

namespace bsdsensors {

NuvotonSensorSourceTable kNCT6686DSensorSources {
    {0x01, {"Local", NuvotonSensorType::kTemp}},
    {0x02, {"TD0P current mode", NuvotonSensorType::kTemp}},
    {0x03, {"TD1P current mode", NuvotonSensorType::kTemp}},
    {0x04, {"TD2P current mode", NuvotonSensorType::kTemp}},
    {0x05, {"TD0P voltage mode", NuvotonSensorType::kTemp}},
    {0x06, {"TD1P voltage mode", NuvotonSensorType::kTemp}},
    {0x07, {"TD2P voltage mode", NuvotonSensorType::kTemp}},
    {0x08, {"Thermistor 14", NuvotonSensorType::kTemp}},
    {0x09, {"Thermistor 15", NuvotonSensorType::kTemp}},
    {0x0a, {"Thermistor 16", NuvotonSensorType::kTemp}},
    {0x0b, {"Thermistor 0", NuvotonSensorType::kTemp}},
    {0x0c, {"Thermistor 1", NuvotonSensorType::kTemp}},
    {0x0d, {"Thermistor 2", NuvotonSensorType::kTemp}},
    {0x0e, {"Thermistor 3", NuvotonSensorType::kTemp}},
    {0x0f, {"Thermistor 4", NuvotonSensorType::kTemp}},
    {0x10, {"Thermistor 5", NuvotonSensorType::kTemp}},
    {0x11, {"Thermistor 6", NuvotonSensorType::kTemp}},
    {0x12, {"Thermistor 7", NuvotonSensorType::kTemp}},
    {0x13, {"Thermistor 8", NuvotonSensorType::kTemp}},
    {0x14, {"Thermistor 9", NuvotonSensorType::kTemp}},
    {0x15, {"Thermistor 10", NuvotonSensorType::kTemp}},
    {0x16, {"Thermistor 11", NuvotonSensorType::kTemp}},
    {0x17, {"Thermistor 12", NuvotonSensorType::kTemp}},
    {0x18, {"Thermistor 13", NuvotonSensorType::kTemp}},
    {0x20, {"PECI Agent0 Domain0", NuvotonSensorType::kTemp}},
    {0x21, {"PECI Agent1 Domain0", NuvotonSensorType::kTemp}},
    {0x22, {"PECI Agent2 Domain0", NuvotonSensorType::kTemp}},
    {0x23, {"PECI Agent3 Domain0", NuvotonSensorType::kTemp}},
    {0x24, {"PECI Agent0 Domain1", NuvotonSensorType::kTemp}},
    {0x25, {"PECI Agent1 Domain1", NuvotonSensorType::kTemp}},
    {0x26, {"PECI Agent2 Domain1", NuvotonSensorType::kTemp}},
    {0x27, {"PECI Agent3 Domain1", NuvotonSensorType::kTemp}},
    {0x28, {"PECI Get DRAM TMP 1", NuvotonSensorType::kTemp}},
    {0x29, {"PECI Get DRAM TMP 2", NuvotonSensorType::kTemp}},
    {0x2a, {"PECI Get DRAM TMP 3", NuvotonSensorType::kTemp}},
    {0x2b, {"PECI Get DRAM TMP 4", NuvotonSensorType::kTemp}},
    {0x30, {"PCH CPU", NuvotonSensorType::kTemp}},
    {0x31, {"PCH CHIP", NuvotonSensorType::kTemp}},
    {0x32, {"PCH CHIP CPU MAX", NuvotonSensorType::kTemp}},
    {0x33, {"PCH MCH", NuvotonSensorType::kTemp}},
    {0x34, {"PCH DIMM0", NuvotonSensorType::kTemp}},
    {0x35, {"PCH DIMM1", NuvotonSensorType::kTemp}},
    {0x36, {"PCH DIMM2", NuvotonSensorType::kTemp}},
    {0x37, {"PCH DIMM3", NuvotonSensorType::kTemp}},
    {0x38, {"SMBus Thermal Sensor 0", NuvotonSensorType::kTemp}},
    {0x39, {"SMBus Thermal Sensor 1", NuvotonSensorType::kTemp}},
    {0x3a, {"SMBus Thermal Sensor 2", NuvotonSensorType::kTemp}},
    {0x3b, {"SMBus Thermal Sensor 3", NuvotonSensorType::kTemp}},
    {0x3c, {"SMBus Thermal Sensor 4", NuvotonSensorType::kTemp}},
    {0x3d, {"SMBus Thermal Sensor 5", NuvotonSensorType::kTemp}},
    {0x3e, {"DIMM Thermal Sensor 0", NuvotonSensorType::kTemp}},
    {0x3f, {"DIMM Thermal Sensor 1", NuvotonSensorType::kTemp}},
    {0x40, {"DIMM Thermal Sensor 2", NuvotonSensorType::kTemp}},
    {0x41, {"DIMM Thermal Sensor 3", NuvotonSensorType::kTemp}},
    {0x42, {"AMD TSI Address 90h", NuvotonSensorType::kTemp}},
    {0x43, {"AMD TSI Address 92h", NuvotonSensorType::kTemp}},
    {0x44, {"AMD TSI Address 94h", NuvotonSensorType::kTemp}},
    {0x45, {"AMD TSI Address 96h", NuvotonSensorType::kTemp}},
    {0x46, {"AMD TSI Address 98h", NuvotonSensorType::kTemp}},
    {0x47, {"AMD TSI Address 9Ah", NuvotonSensorType::kTemp}},
    {0x48, {"AMD TSI Address 9Ch", NuvotonSensorType::kTemp}},
    {0x49, {"AMD TSI Address 9Dh", NuvotonSensorType::kTemp}},
    {0x50, {"Virtual Input 0", NuvotonSensorType::kTemp}},
    {0x51, {"Virtual Input 1", NuvotonSensorType::kTemp}},
    {0x52, {"Virtual Input 2", NuvotonSensorType::kTemp}},
    {0x53, {"Virtual Input 3", NuvotonSensorType::kTemp}},
    {0x54, {"Virtual Input 4", NuvotonSensorType::kTemp}},
    {0x55, {"Virtual Input 5", NuvotonSensorType::kTemp}},
    {0x56, {"Virtual Input 6", NuvotonSensorType::kTemp}},
    {0x57, {"Virtual Input 7", NuvotonSensorType::kTemp}},
    {0x60, {"Vcc", NuvotonSensorType::kVolt}},
    {0x61, {"3Vsb", NuvotonSensorType::kVolt}},
    {0x62, {"AVsb", NuvotonSensorType::kVolt}},
    {0x64, {"Vbat", NuvotonSensorType::kVolt}},
    {0x66, {"Vin0", NuvotonSensorType::kVolt}},
    {0x67, {"Vin1", NuvotonSensorType::kVolt}},
    {0x68, {"Vin2", NuvotonSensorType::kVolt}},
    {0x69, {"Vin3", NuvotonSensorType::kVolt}},
    {0x6a, {"Vin4", NuvotonSensorType::kVolt}},
    {0x6b, {"Vin5", NuvotonSensorType::kVolt}},
    {0x6c, {"Vin6", NuvotonSensorType::kVolt}},
    {0x6d, {"Vin7", NuvotonSensorType::kVolt}},
    {0x6e, {"Vin8", NuvotonSensorType::kVolt}},
    {0x6f, {"Vin9", NuvotonSensorType::kVolt}},
    {0x70, {"Vin10", NuvotonSensorType::kVolt}},
    {0x71, {"Vin11", NuvotonSensorType::kVolt}},
    {0x72, {"Vin12", NuvotonSensorType::kVolt}},
    {0x73, {"Vin13", NuvotonSensorType::kVolt}},
    {0x74, {"Vin14", NuvotonSensorType::kVolt}},
    {0x75, {"Vin15", NuvotonSensorType::kVolt}},
    {0x76, {"Vin16", NuvotonSensorType::kVolt}},
};

const NuvotonChipInfo kNCT6686D = {
    .device_id_to_name = {{0xC73A, "NCT6686D"}},
    .vendor_id_addr = {0, 0x4F},
    .volt_unit = 0.016,
    .use_ec_space = true,
    .sensor_sources = kNCT6686DSensorSources
};

NuvotonChipInfo AddMultiSensors(NuvotonChipInfo chip) {
    for (int i = 0; i < 32; ++i) {
        chip.multi_sensors.push_back({
          .index = i,
          .select = {0, 0xA0 + i, {6, 0}},
          .value_high = {0, i * 2},
          .value_low = {0, i * 2 + 1},
          });
    }
    for (int i = 0; i < 16; ++i) {
        if (i < 8) {
            chip.fans.push_back({
                    .name = "FAN" + std::to_string(i),
                    .rpm_high = {0, 0x40 + i * 2},
                    .rpm_low = {0, 0x41 + i * 2},
                    });
        } else {
            chip.fans.push_back({
                    .name = "FAN" + std::to_string(i),
                    .rpm_high = {0, 0x40 + i * 2},
                    .rpm_low = {0, 0x41 + i * 2},
                    });
        }
    }
    return chip;
}

RegisterChip<NuvotonChipInfo> kRegisterNCT6686D(AddMultiSensors(kNCT6686D));

}
