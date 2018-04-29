/*
 * temp_sensor.h
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#ifndef __BSDSENSORS_TEMP_SENSOR_H__
#define __BSDSENSORS_TEMP_SENSOR_H__

#include <string>

class TempSensor {
   public:
    // Temperature in Celsius
    virtual double value() = 0;
    virtual std::string name() = 0;
};

#endif  // __BSDSENSORS_TEMP_SENSOR_H__
