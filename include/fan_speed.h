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

namespace bsdsensors {

class FanSpeed : public DumpAble {
  public:
    virtual ~FanSpeed() {}

    virtual double value() const = 0;
    virtual std::string name() const = 0;
};

}  // namespace bsdsensors

#endif  // __BSDSENSORS_FAN_SPEED_H__
