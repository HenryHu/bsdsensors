/*
 * ite_fan_control.h
 * Copyright (C) 2025 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#ifndef __BSDSENSORS_ITE_FAN_CONTROL_H__
#define __BSDSENSORS_ITE_FAN_CONTROL_H__

#include "fan_control.h"

#include <iostream>

#include "ite_chip_info.h"

namespace bsdsensors {

class ITEFanControl : public FanControl {
  public:
    virtual ~ITEFanControl() = default;

    virtual std::string name() = 0;

    virtual Status GetSensorValues(FanControlProto& proto) = 0;
};

std::unique_ptr<ITEFanControl> CreateITEFanControl(
        const ITEFanControlInfo& info, ITEChip* chip);

}

#endif // __BSDSENSORS_ITE_FAN_CONTROL_H__
