/*
 * ite_chip_info.h
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#ifndef __BSDSENSORS_ITE_CHIP_INFO_H__
#define __BSDSENSORS_ITE_CHIP_INFO_H__

#include "chip_info.h"
#include "ite_chip.h"

#include <string>

namespace bsdsensors {

struct ITETempInfo {
    std::string name;
    ITEChip::AddressType value;
};

struct ITEVoltInfo {
    std::string name;
    ITEChip::AddressType value;
    // out = value * 0.012 * alpha + beta
    double alpha = 1.0, beta = 0.0;
};

struct ITEFanSpeedInfo {
    std::string name;
    ITEChip::AddressType count;
    ITEChip::AddressType count_high;
    ITEChip::AddressType wide_mode;
    ITEChip::AddressType enable;
    ITEChip::AddressType output_mode;
};

struct ITEFanControlInfo {
    std::string name;
    ITEChip::AddressType mode_select;
    ITEChip::AddressType pwm;
    ITEChip::AddressType temp_input_select;
    std::map<uint8_t, std::string> temp_inputs;
};

struct ITEChipInfo {
    std::map<uint16_t, std::string> device_id_to_name;
    std::vector<ITETempInfo> temps;
    std::vector<ITEVoltInfo> volts;
    std::vector<ITEFanSpeedInfo> fan_speeds;
    std::vector<ITEFanControlInfo> fan_controls;
};

}  // namespace bsdsensors

#endif  // __BSDSENSORS_ITE_CHIP_INFO_H__
