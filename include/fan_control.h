/*
 * fan_control.h
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#ifndef __BSDSENSORS_FAN_CONTROL_H__
#define __BSDSENSORS_FAN_CONTROL_H__

#include "status.h"
#include "util.h"

#include "fan_control.pb.h"

#include <string>

namespace bsdsensors {

class FanControl : public DumpAble {
   public:
    virtual double current_percent() const = 0;
};

class FanControlMethod : public DumpAble {
   public:
    virtual std::string name() const = 0;
    virtual Status Observe() = 0;
    virtual Status Apply() = 0;

    virtual void FillState(FanControlMethodProto* proto) = 0;
};

}  // namespace bsdsensors

#endif  // __BSDSENSORS_FAN_CONTROL_H__
