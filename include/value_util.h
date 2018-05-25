/*
 * value_util.h
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#ifndef __BSDSENSORS_VALUE_UTIL_H__
#define __BSDSENSORS_VALUE_UTIL_H__

#include "sensors.pb.h"

#include <iostream>

namespace bsdsensors {

extern void PrintSensorValues(const SensorsProto& sensors, std::ostream& out);
extern void PrintTempValue(const TemperatureProto& temp, std::ostream& out);
extern void PrintFanSpeedValue(const FanProto& fan_speed, std::ostream& out);
extern void PrintVoltValue(const VoltageProto& volt, std::ostream& out);
extern std::ostream& operator<<(std::ostream& out,
                                const FanControlProto& fan_control);

void PrintSelectedSensors(const SensorsProto& sensors,
                          const std::string& selected, bool value_only,
                          std::ostream& out);

}  // namespace bsdsensors

#endif  // __BSDSENSORS_VALUE_UTIL_H__
