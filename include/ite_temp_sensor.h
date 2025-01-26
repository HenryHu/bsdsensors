/*
 * ite_temp_sensor.h
 * Copyright (C) 2025 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#ifndef __BSDSENSORS_ITE_TEMP_SENSOR_H__
#define __BSDSENSORS_ITE_TEMP_SENSOR_H__

#include "temp_sensor.h"
#include "ite_chip.h"
#include "ite_chip_info.h"

#include <memory>
#include <string>

namespace bsdsensors {

class ITETempSensor : public TempSensor {
   public:
    virtual ~ITETempSensor() {}

    double value() override = 0;
    std::string name() override = 0;
};

std::unique_ptr<ITETempSensor> CreateITETempSensor(
    const ITETempInfo& info, ITEChip* chip);

}  // namespace bsdsensors

#endif  // __BSDSENSORS_NUVOTON_TEMP_SENSOR_H__

