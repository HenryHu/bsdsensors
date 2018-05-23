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
#include "nuvoton_fan_control.pb.h"
#include "status.h"
#include <memory>

namespace bsdsensors {

class NuvotonFanControl : public FanControl {
   public:
    virtual Status SetControlMode(NuvotonFanControlMode target) = 0;
    virtual Status GetCurrentMethod(FanControlMethod** method) = 0;
};

class NuvotonFanControlManual : public FanControlMethod {
   public:
    virtual void SetPower(int power) = 0;
};
class NuvotonFanControlThermalCruise : public FanControlMethod {};
class NuvotonFanControlSpeedCruise : public FanControlMethod {};
class NuvotonFanControlSmartFan4 : public FanControlMethod {};

std::unique_ptr<NuvotonFanControl> CreateNuvotonFanControl(
    const NuvotonFanControlInfo& info, NuvotonChip* chip);

void PrintNuvotonFanControlMethod(const nuvoton::FanControlMethod& method,
                                  std::ostream& out);

}  // namespace bsdsensors

#endif  // __BSDSENSORS_NUVOTON_FAN_CONTROL_H__
