/*
 * ite_fan_speed.h
 * Copyright (C) 2025 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#ifndef __BSDSENSORS_ITE_FAN_SPEED_H__
#define __BSDSENSORS_ITE_FAN_SPEED_H__

#include "ite_chip.h"
#include "ite_chip_info.h"
#include "fan_speed.h"

#include <memory>
#include <string>

namespace bsdsensors {

class ITEFanSpeed : public FanSpeed {
   public:
    virtual ~ITEFanSpeed() {}

    double value() const override = 0;
    std::string name() const override = 0;
};

std::unique_ptr<ITEFanSpeed> CreateITEFanSpeed(
    const ITEFanSpeedInfo& info, ITEChip* chip);

}  // namespace bsdsensors

#endif  // __BSDSENSORS_NUVOTON_FAN_SPEED_H__


