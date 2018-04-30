/*
 * nuvoton_fan_control.h
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#ifndef __BSDSENSORS_NUVOTON_FAN_CONTROL_H__
#define __BSDSENSORS_NUVOTON_FAN_CONTROL_H__

#include "fan_control.h"
#include "nuvoton_chip_info.h"
#include <memory>

class NuvotonFanControl : public FanControl {
   public:
    double current_percent() override = 0;
};

std::unique_ptr<NuvotonFanControl> CreateNuvotonFanControl(
    const NuvotonFanControlInfo& info, NuvotonChip* chip);

#endif  // __BSDSENSORS_NUVOTON_FAN_CONTROL_H__
