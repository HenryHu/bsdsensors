/*
 * nuvoton_temp_sensor.h
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#ifndef __BSDSENSORS_NUVOTON_TEMP_SENSOR_H__
#define __BSDSENSORS_NUVOTON_TEMP_SENSOR_H__

#include "temp_sensor.h"

#include <memory>
#include <string>

class NuvotonTempSensor : public TempSensor {
   public:
    double value() override = 0;
    std::string name() override = 0;
};

std::unique_ptr<NuvotonTempSensor> CreateNuvotonTempSensor(
    const std::string& name);

#endif  // __BSDSENSORS_NUVOTON_TEMP_SENSOR_H__
