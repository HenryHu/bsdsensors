/*
 * fan_speed.h
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#ifndef __BSDSENSORS_FAN_SPEED_H__
#define __BSDSENSORS_FAN_SPEED_H__

#include <string>

class FanSpeed {
   public:
    virtual double value() = 0;
    virtual std::string name() = 0;
};

#endif  // __BSDSENSORS_FAN_SPEED_H__
