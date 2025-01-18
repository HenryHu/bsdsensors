/*
 * nuvoton_chip_info.cc
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "nuvoton_chip_info.h"

namespace bsdsensors {

const std::map<NuvotonTempSource, std::string> kNuvotonTempSourceName{
    {NuvotonTempSource::kSourceSYSTIN, "SYSTIN"},
    {NuvotonTempSource::kSourceCPUTIN, "CPUTIN"},
    {NuvotonTempSource::kSourceAUXTIN0, "AUXTIN0"},
    {NuvotonTempSource::kSourceAUXTIN1, "AUXTIN1"},
    {NuvotonTempSource::kSourceAUXTIN2, "AUXTIN2"},
    {NuvotonTempSource::kSourceAUXTIN3, "AUXTIN3"},
    {NuvotonTempSource::kSourceAUXTIN4, "AUXTIN4"},
    {NuvotonTempSource::kSourceSMBUSMASTER0, "SMBUS0"},
    {NuvotonTempSource::kSourceSMBUSMASTER1, "SMBUS1"},
    {NuvotonTempSource::kSourceSMBUSMASTER2, "SMBUS2"},
    {NuvotonTempSource::kSourceSMBUSMASTER3, "SMBUS3"},
    {NuvotonTempSource::kSourceSMBUSMASTER4, "SMBUS4"},
    {NuvotonTempSource::kSourceSMBUSMASTER5, "SMBUS5"},
    {NuvotonTempSource::kSourceSMBUSMASTER6, "SMBUS6"},
    {NuvotonTempSource::kSourceSMBUSMASTER7, "SMBUS7"},
    {NuvotonTempSource::kSourcePECI0, "PECI0"},
    {NuvotonTempSource::kSourcePECI1, "PECI1"},
    {NuvotonTempSource::kSourcePCHCPUMAX, "PCH_CPU_MAX"},
    {NuvotonTempSource::kSourcePCH, "PCH"},
    {NuvotonTempSource::kSourcePCHCPU, "PCH_CPU"},
    {NuvotonTempSource::kSourcePCHMCH, "MCH"},
    {NuvotonTempSource::kSourceDIM0, "DIMM0"},
    {NuvotonTempSource::kSourceDIM1, "DIMM1"},
    {NuvotonTempSource::kSourceDIM2, "DIMM2"},
    {NuvotonTempSource::kSourceDIM3, "DIMM3"},
    {NuvotonTempSource::kSourceBYTE, "TSI_BYTE"},
    {NuvotonTempSource::kSourceBYTE0, "TSI_BYTE0"},
    {NuvotonTempSource::kSourceBYTE1, "TSI_BYTE1"},
    {NuvotonTempSource::kSource27, "Source27"},
    {NuvotonTempSource::kSource28, "Source28"},
    {NuvotonTempSource::kSource29, "Source29"},
    {NuvotonTempSource::kSource30, "Source30"},
    {NuvotonTempSource::kSource31, "Source31"},
    {NuvotonTempSource::kSourceVirtualTemp1, "VirtualTemp1"},
    {NuvotonTempSource::kSourceVirtualTemp2, "VirtualTemp2"},
    {NuvotonTempSource::kSourceVirtualTemp3, "VirtualTemp3"},
    {NuvotonTempSource::kSourcePECI0Calib, "PECI0Calibration"},
    {NuvotonTempSource::kSourcePECI1Calib, "PECI1Calibration"},
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
