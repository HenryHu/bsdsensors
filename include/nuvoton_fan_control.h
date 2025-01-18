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
    virtual ~NuvotonFanControl() {}

    virtual Status SetControlMode(NuvotonFanControlMode target) = 0;
    virtual Status SetControlMode(const std::string& target) = 0;
    virtual Status GetCurrentMethod(FanControlMethod** method) = 0;

    virtual Status SetTempSource(const std::string& name) = 0;

    virtual void FillState(FanControlProto* proto) = 0;
    virtual Status HandleRequest(const FanControlRequest& request) = 0;
};

class NuvotonFanControlManual : public FanControlMethod {
   public:
    virtual Status SetPower(int power) = 0;
};
class NuvotonFanControlThermalCruise : public FanControlMethod {};
class NuvotonFanControlSpeedCruise : public FanControlMethod {};
class NuvotonFanControlSmartFan4 : public FanControlMethod {
   public:
    virtual Status HandleRequest(const nuvoton::SmartFanIVRequest& request) = 0;
};

std::unique_ptr<NuvotonFanControl> CreateNuvotonFanControl(
    const NuvotonFanControlInfo& info, const NuvotonTempSourceTable& table,
    NuvotonChip* chip);

std::unique_ptr<NuvotonFanControl> CreateDummyNuvotonFanControl();

std::ostream& operator<<(std::ostream& out,
                         const nuvoton::FanControlMethod& method);

Status ParseNuvotonFanControlMode(const std::string& str_mode,
                                  NuvotonFanControlMode* mode);

}  // namespace bsdsensors

#endif  // __BSDSENSORS_NUVOTON_FAN_CONTROL_H__
