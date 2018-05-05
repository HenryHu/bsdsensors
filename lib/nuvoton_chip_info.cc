/*
 * nuvoton_chip_info.cc
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "nuvoton_chip_info.h"

namespace bsdsensors {

KnownChips<NuvotonChipInfo> NuvotonChips;

std::string GetNuvotonSourceName(NuvotonTempSource source) {
    switch (source) {
        case kSourceSYSTIN: {
            return "SYSTIN";
        }
        case kSourceCPUTIN: {
            return "CPUTIN";
        }
        case kSourceAUXTIN0: {
            return "AUXTIN0";
        }
        case kSourceAUXTIN1: {
            return "AUXTIN1";
        }
        case kSourceAUXTIN2: {
            return "AUXTIN2";
        }
        case kSourceAUXTIN3: {
            return "AUXTIN3";
        }
        case kSourceReserved: {
            break;
        }
        case kSourceSMBUSMASTER0: {
            break;
        }
        case kSourceSMBUSMASTER1: {
            break;
        }
        case kSourceSMBUSMASTER2: {
            break;
        }
        case kSourceSMBUSMASTER3: {
            break;
        }
        case kSourceSMBUSMASTER4: {
            break;
        }
        case kSourceSMBUSMASTER5: {
            break;
        }
        case kSourceSMBUSMASTER6: {
            break;
        }
        case kSourceSMBUSMASTER7: {
            break;
        }
        case kSourcePECI0: {
            return "PECI0";
        }
        case kSourcePECI1: {
            return "PECI1";
        }
        case kSourcePCHCPUMAX: {
            return "PCH_CPU_MAX";
        }
        case kSourcePCH: {
            return "PCH";
        }
        case kSourcePCHCPU: {
            return "PCH_CPU";
        }
        case kSourcePCHMCH: {
            return "MCH";
        }
        case kSourceDIM0: {
            return "DIM0";
        }
        case kSourceDIM1: {
            return "DIM1";
        }
        case kSourceDIM2: {
            return "DIM2";
        }
        case kSourceDIM3: {
            return "DIM3";
        }
        case kSourceBYTE: {
            return "TSI_BYTE";
        }
        case kSource27: {
            return "Source27";
        }
        case kSource28: {
            return "Source28";
        }
        case kSource29: {
            return "Source29";
        }
        case kSource30: {
            return "Source30";
        }
        case kSource31: {
            return "Source31";
        }
    }
    return "Unknown";
}

}  // namespace bsdsensors
