/*
 * ite_chip_info.h
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#ifndef __BSDSENSORS_ITE_CHIP_INFO_H__
#define __BSDSENSORS_ITE_CHIP_INFO_H__

#include "chip_info.h"

#include <string>

namespace bsdsensors {

struct ITEChipInfo {
    std::map<uint16_t, std::string> device_id_to_name;
};

}  // namespace bsdsensors

#endif  // __BSDSENSORS_ITE_CHIP_INFO_H__
