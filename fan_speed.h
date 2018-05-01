/*
 * fan_speed.h
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#ifndef __BSDSENSORS_FAN_SPEED_H__
#define __BSDSENSORS_FAN_SPEED_H__

#include "util.h"
#include <string>

class FanSpeed : public DumpAble {
   public:
    virtual double value() const = 0;
    virtual std::string name() const = 0;
};

#endif  // __BSDSENSORS_FAN_SPEED_H__
