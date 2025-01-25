/*
 * nuvoton_multi_sensor.h
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#ifndef __BSDSENSORS_NUVOTON_MULTI_SENSOR_H__
#define __BSDSENSORS_NUVOTON_MULTI_SENSOR_H__

#include "nuvoton_chip_info.h"

#include <memory>
#include <string>

namespace bsdsensors {

class NuvotonMultiSensor : public DumpAble {
   public:
    virtual ~NuvotonMultiSensor() {}

    virtual double value() = 0;
    virtual std::string name() = 0;

    virtual const NuvotonSensorSourceInfo* GetSource() = 0;
    virtual Status SetSource(const std::string& target) = 0;
};

std::unique_ptr<NuvotonMultiSensor> CreateNuvotonMultiSensor(
    const NuvotonMultiSensorInfo& info, const NuvotonSensorSourceTable& table,
    NuvotonChip* chip);

}  // namespace bsdsensors

#endif  // __BSDSENSORS_NUVOTON_MULTI_SENSOR_H__
