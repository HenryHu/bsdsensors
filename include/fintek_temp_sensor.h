/*
 * fintek_temp_sensor.h
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#ifndef __BSDSENSORS_FINTEK_TEMP_SENSOR_H__
#define __BSDSENSORS_FINTEK_TEMP_SENSOR_H__

#include "temp_sensor.h"
#include "fintek_chip_info.h"
#include "fintek_chip.h"

namespace bsdsensors {

class FintekTempSensor : public TempSensor {};

std::unique_ptr<FintekTempSensor> CreateFintekTempSensor(
    const FintekTempInfo& info, FintekChip* chip);

};  // namespace bsdsensors

#endif  // __BSDSENSORS_FINTEK_TEMP_SENSOR_H__
