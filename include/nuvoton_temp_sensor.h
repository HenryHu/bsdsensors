/*
 * nuvoton_temp_sensor.h
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#ifndef __BSDSENSORS_NUVOTON_TEMP_SENSOR_H__
#define __BSDSENSORS_NUVOTON_TEMP_SENSOR_H__

#include "temp_sensor.h"
#include "nuvoton_chip_info.h"

#include <memory>
#include <string>

namespace bsdsensors {

enum NuvotonTempSource {
    kSourceSYSTIN = 1,
    kSourceCPUTIN = 2,
    kSourceAUXTIN0 = 3,
    kSourceAUXTIN1 = 4,
    kSourceAUXTIN2 = 5,
    kSourceAUXTIN3 = 6,
    kSourceReserved = 7,
    kSourceSMBUSMASTER0 = 8,
    kSourceSMBUSMASTER1 = 9,
    kSourceSMBUSMASTER2 = 10,
    kSourceSMBUSMASTER3 = 11,
    kSourceSMBUSMASTER4 = 12,
    kSourceSMBUSMASTER5 = 13,
    kSourceSMBUSMASTER6 = 14,
    kSourceSMBUSMASTER7 = 15,
    kSourcePECI0 = 16,
    kSourcePECI1 = 17,
    kSourcePCHCPUMAX = 18,
    kSourcePCH = 19,
    kSourcePCHCPU = 20,
    kSourcePCHMCH = 21,
    kSourceDIM0 = 22,
    kSourceDIM1 = 23,
    kSourceDIM2 = 24,
    kSourceDIM3 = 25,
    kSourceBYTE = 26,
    kSource27 = 27,
    kSource28 = 28,
    kSource29 = 29,
    kSource30 = 30,
    kSource31 = 31,
};

std::string GetSourceName(NuvotonTempSource source);

class NuvotonTempSensor : public TempSensor {
   public:
    double value() override = 0;
    std::string name() override = 0;

    virtual NuvotonTempSource GetSource() = 0;
    virtual Status SetSource(NuvotonTempSource target) = 0;
};

std::unique_ptr<NuvotonTempSensor> CreateNuvotonTempSensor(
    const NuvotonTempInfo& info, NuvotonChip* chip);

}  // namespace bsdsensors

#endif  // __BSDSENSORS_NUVOTON_TEMP_SENSOR_H__
