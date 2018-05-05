/*
 * fintek_volt_sensor.h
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#ifndef __BSDSENSORS_FINTEK_VOLT_SENSOR_H__
#define __BSDSENSORS_FINTEK_VOLT_SENSOR_H__

#include "volt_sensor.h"
#include "fintek_chip_info.h"
#include "fintek_chip.h"

#include <memory>

namespace bsdsensors {

class FintekVoltSensor : public VoltSensor {};

std::unique_ptr<FintekVoltSensor> CreateFintekVoltSensor(
    const FintekVoltInfo& info, FintekChip* chip);

}  // namespace bsdsensors

#endif  // __BSDSENSORS_FINTEK_VOLT_SENSOR_H__
