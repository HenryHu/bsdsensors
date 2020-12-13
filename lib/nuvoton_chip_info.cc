/*
 * nuvoton_chip_info.cc
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "nuvoton_chip_info.h"

namespace bsdsensors {

const std::map<NuvotonTempSource, std::string> kNuvotonTempSourceName{
    {kSourceSYSTIN, "SYSTIN"},
    {kSourceCPUTIN, "CPUTIN"},
    {kSourceAUXTIN0, "AUXTIN0"},
    {kSourceAUXTIN1, "AUXTIN1"},
    {kSourceAUXTIN2, "AUXTIN2"},
    {kSourceAUXTIN3, "AUXTIN3"},
    {kSourceReserved, "Reserved"},
    {kSourceSMBUSMASTER0, "SMBUS0"},
    {kSourceSMBUSMASTER1, "SMBUS1"},
    {kSourceSMBUSMASTER2, "SMBUS2"},
    {kSourceSMBUSMASTER3, "SMBUS3"},
    {kSourceSMBUSMASTER4, "SMBUS4"},
    {kSourceSMBUSMASTER5, "SMBUS5"},
    {kSourceSMBUSMASTER6, "SMBUS6"},
    {kSourceSMBUSMASTER7, "SMBUS7"},
    {kSourcePECI0, "PECI0"},
    {kSourcePECI1, "PECI1"},
    {kSourcePCHCPUMAX, "PCH_CPU_MAX"},
    {kSourcePCH, "PCH"},
    {kSourcePCHCPU, "PCH_CPU"},
    {kSourcePCHMCH, "MCH"},
    {kSourceDIM0, "DIM0"},
    {kSourceDIM1, "DIM1"},
    {kSourceDIM2, "DIM2"},
    {kSourceDIM3, "DIM3"},
    {kSourceBYTE, "TSI_BYTE"},
    {kSource27, "Source27"},
    {kSource28, "Source28"},
    {kSource29, "Source29"},
    {kSource30, "Source30"},
    {kSource31, "Source31"},
    {kSourceVirtualTemp1, "VirtualTemp1"},
    {kSourceVirtualTemp2, "VirtualTemp2"},
    {kSourceVirtualTemp3, "VirtualTemp3"},
    {kSourcePECI0Calib, "PECI0Calibration"},
    {kSourcePECI1Calib, "PECI1Calibration"},
};

std::string GetNuvotonSourceName(NuvotonTempSource source) {
    auto entry = kNuvotonTempSourceName.find(source);
    if (entry != kNuvotonTempSourceName.end()) {
        return entry->second;
    }
    return "Unknown";
}

Status GetNuvotonSourceByName(const std::string& name,
                              NuvotonTempSource* source) {
    for (const auto& entry : kNuvotonTempSourceName) {
        if (entry.second == name) {
            *source = entry.first;
            return OkStatus();
        }
    }
    return Status(EINVAL, "Unknown source");
}

}  // namespace bsdsensors
