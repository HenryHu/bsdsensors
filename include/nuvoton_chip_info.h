/*
 * nuvoton_chip_info.h
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#ifndef __BSDSENSORS_NUVOTON_CHIP_INFO_H__
#define __BSDSENSORS_NUVOTON_CHIP_INFO_H__

#include <map>
#include <cstdint>
#include <string>
#include <vector>

#include "nuvoton_chip.h"

struct NuvotonSmartFanInfo {
    bool available;
};

struct NuvotonSmartFan4ControlPointInfo {
    NuvotonChip::AddressType temp;
    NuvotonChip::AddressType power;
};

struct NuvotonSmartFan4Info {
    bool available;
    std::vector<NuvotonSmartFan4ControlPointInfo> control_points;
};

enum NuvotonFanControlMode {
    kManualMode = 0,
    kThermalCruise = 1,
    kSpeedCruise = 2,
    kSmartFan4 = 4,
};

struct NuvotonFanControlInfo {
    NuvotonChip::AddressType mode_select, output_value_write;
    bool support_dc;
    // If support_dc = false, then output_type is invalid
    NuvotonChip::AddressType output_type, output_value_read;
    NuvotonChip::AddressType temp_source, temp_value_int, temp_value_frac;
    NuvotonSmartFanInfo smart_fan;
    NuvotonSmartFan4Info smart_fan4;
};

struct NuvotonFanInfo {
    std::string name;
    NuvotonChip::AddressType rpm_high, rpm_low;
    NuvotonFanControlInfo control;
};

struct NuvotonTempInfo {
    std::string name;
    bool has_frac_part;
    NuvotonChip::AddressType val_int, val_frac;
    bool has_peci_frac;
    bool can_select;
    NuvotonChip::AddressType select;
};

struct NuvotonVoltInfo {
    std::string name;
    NuvotonChip::AddressType addr;
    // Result = raw value * alpha + beta
    double alpha = 1.0, beta = 0.0;
};

struct NuvotonChipInfo {
    std::string name;
    NuvotonChip::AddressType vendor_id_addr;
    std::vector<NuvotonFanInfo> fans;
    std::vector<NuvotonTempInfo> temps;
    std::vector<NuvotonVoltInfo> volts;
};

extern const std::map<uint16_t, NuvotonChipInfo> kKnownNuvotonChips;

#endif  // __BSDSENSORS_NUVOTON_CHIP_INFO_H__
