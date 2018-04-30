/*
 * fan_control.h
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#ifndef __BSDSENSORS_FAN_CONTROL_H__
#define __BSDSENSORS_FAN_CONTROL_H__

class FanControl {
   public:
    virtual double current_percent() = 0;
};

#endif  // __BSDSENSORS_FAN_CONTROL_H__
