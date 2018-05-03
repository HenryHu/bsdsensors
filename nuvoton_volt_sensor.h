/*
 * nuvoton_volt_sensor.h
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#ifndef __BSDSENSORS_NUVOTON_VOLT_SENSOR_H__
#define __BSDSENSORS_NUVOTON_VOLT_SENSOR_H__

#include "volt_sensor.h"
#include "nuvoton_chip_info.h"

#include <memory>

class NuvotonVoltSensor : public VoltSensor {};

std::unique_ptr<NuvotonVoltSensor> CreateNuvotonVoltSensor(
    const NuvotonVoltInfo& info, NuvotonChip* chip);

#endif  // __BSDSENSORS_NUVOTON_VOLT_SENSOR_H__
