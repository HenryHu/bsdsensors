/*
 * fintek_fan.h
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#ifndef __BSDSENSORS_FINTEK_FAN_H__
#define __BSDSENSORS_FINTEK_FAN_H__

#include "fan_speed.h"
#include "fan_control.h"
#include "fintek_chip_info.h"

#include <ostream>

namespace bsdsensors {

class FintekFan : public FanSpeed, public FanControl {
   public:
    void DumpInfo(std::ostream& out) override = 0;
};

std::unique_ptr<FintekFan> CreateFintekFan(const FintekFanInfo& info,
                                           FintekChip* chip);

}  // namespace bsdsensors

#endif  // __BSDSENSORS_FINTEK_FAN_H__
