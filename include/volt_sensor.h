/*
 * volt_sensor.h
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#ifndef __BSDSENSORS_VOLT_SENSOR_H__
#define __BSDSENSORS_VOLT_SENSOR_H__

#include "util.h"

#include <string>

namespace bsdsensors {

class VoltSensor : public DumpAble {
  public:
    virtual ~VoltSensor() {}

    virtual std::string name() = 0;
    virtual double value() = 0;
};

}  // namespace bsdsensors

#endif  // __BSDSENSORS_VOLT_SENSOR_H__
