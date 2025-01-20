/*
 * fintek_chip_info.h
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#ifndef __BSDSENSORS_FINTEK_CHIP_INFO_H__
#define __BSDSENSORS_FINTEK_CHIP_INFO_H__

#include "chip_info.h"
#include "fintek_chip.h"

#include <string>
#include <vector>

namespace bsdsensors {

struct FintekVoltInfo {
    std::string name;
    FintekAddress value, under, over;
    // Result = value * alpha + beta
    double alpha, beta;
};

struct FintekFanInfo {
    std::string name;
    FintekAddress count_high, count_low;
    FintekAddress duty, duty_write, mode;
    FintekAddress temp_src;
};

struct FintekTempInfo {
    std::string name;
    FintekAddress value, over, high, value_frac;
};

struct FintekChipInfo {
    std::map<uint16_t, std::string> device_id_to_name;
    std::vector<FintekFanInfo> fans;
    std::vector<FintekTempInfo> temps;
    std::vector<FintekVoltInfo> volts;
};

}  // namespace bsdsensors

#endif  // __BSDSENSORS_FINTEK_CHIP_INFO_H__
