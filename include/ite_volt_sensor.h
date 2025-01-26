/*
 * ite_volt_sensor.h
 * Copyright (C) 2025 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#ifndef __BSDSENSORS_ITE_VOLT_SENSOR_H__
#define __BSDSENSORS_ITE_VOLT_SENSOR_H__

#include "volt_sensor.h"
#include "ite_chip.h"
#include "ite_chip_info.h"

#include <memory>
#include <string>

namespace bsdsensors {

class ITEVoltSensor : public VoltSensor {
   public:
    virtual ~ITEVoltSensor() {}

    double value() override = 0;
    std::string name() override = 0;
};

std::unique_ptr<ITEVoltSensor> CreateITEVoltSensor(
    const ITEVoltInfo& info, ITEChip* chip);

}  // namespace bsdsensors

#endif  // __BSDSENSORS_NUVOTON_VOLT_SENSOR_H__
