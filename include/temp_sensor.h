/*
 * temp_sensor.h
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#ifndef __BSDSENSORS_TEMP_SENSOR_H__
#define __BSDSENSORS_TEMP_SENSOR_H__

#include "util.h"
#include <string>

namespace bsdsensors {

class TempSensor : public DumpAble {
   public:
    // Temperature in Celsius
    virtual double value() = 0;
    virtual std::string name() = 0;
};

}  // namespace bsdsensors

#endif  // __BSDSENSORS_TEMP_SENSOR_H__
