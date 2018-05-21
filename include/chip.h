/*
 * chip.h
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#ifndef __BSDSENSORS_CHIP_H__
#define __BSDSENSORS_CHIP_H__

#include "util.h"
#include "status.h"
#include "sensors.pb.h"

namespace bsdsensors {

class Chip : public DumpAble {
   public:
    virtual ~Chip() {}

    virtual bool Detect() = 0;

    virtual Status GetSensorValues(SensorsProto* sensors) = 0;
};

}  // namespace bsdsensors

#endif  // __BSDSENSORS_CHIP_H__
