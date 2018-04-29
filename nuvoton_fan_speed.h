/*
 * nuvoton_fan_speed.h
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#ifndef __BSDSENSORS_NUVOTON_FAN_SPEED_H__
#define __BSDSENSORS_NUVOTON_FAN_SPEED_H__

#include "fan_speed.h"
#include "nuvoton_chip_info.h"

class NuvotonFanSpeed : public FanSpeed {};

std::unique_ptr<NuvotonFanSpeed> CreateNuvotonFanSpeed(
    const NuvotonFanInfo& info, NuvotonChip* chip);

#endif  // __BSDSENSORS_NUVOTON_FAN_SPEED_H__
