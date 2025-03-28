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
#include "request.pb.h"
#include "testdata.pb.h"

#include <string>

namespace bsdsensors {

class Chip : public DumpAble {
   public:
    virtual ~Chip() {}

    virtual bool Detect() = 0;

    virtual Status GetSensorValues(SensorsProto* sensors) = 0;

    virtual std::string name() = 0;
    virtual void set_name(const std::string& name) = 0;

    virtual Status ProcessRequest(const Request& request) { return OkStatus(); }

    virtual void DumpAll(std::ostream& out) {
        out << "DumpAll not implemented." << std::endl;
    }

    virtual TestData DumpProto() { return {}; }
};

}  // namespace bsdsensors

#endif  // __BSDSENSORS_CHIP_H__
