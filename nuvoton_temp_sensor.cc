/*
 * nuvoton_temp_sensor.cc
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "nuvoton_temp_sensor.h"

#include <cmath>

using std::string;

string GetSourceName(NuvotonTempSource source) {
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
            break;
        }
        case kSourcePCH: {
            return "PCH";
        }
        case kSourcePCHCPU: {
            break;
        }
        case kSourcePCHMCH: {
            break;
        }
        case kSourceDIM0: {
            break;
        }
        case kSourceDIM1: {
            break;
        }
        case kSourceDIM2: {
            break;
        }
        case kSourceDIM3: {
            break;
        }
        case kSourceBYTE: {
            break;
        }
        case kSource27: {
            return "Source27";
        }
        case kSource28: {
            return "Source28";
            break;
        }
        case kSource29: {
            return "Source29";
            break;
        }
        case kSource30: {
            return "Source30";
            break;
        }
        case kSource31: {
            return "Source31";
        }
    }
    return "Unknown";
}

class NuvotonTempSensorImpl : public NuvotonTempSensor {
   public:
    NuvotonTempSensorImpl(const NuvotonTempInfo& info, NuvotonChip* chip)
        : info_(info), chip_(chip) {}

    double value() override {
        uint8_t val_int;
        chip_->ReadByte(info_.val_int, &val_int);
        double ret = val_int;
        if (info_.has_frac_part) {
            uint8_t val_frac;
            chip_->ReadByte(info_.val_frac, &val_frac);
            if (info_.has_peci_frac) {
                if (val_frac & 0x02) {
                    ret += 0.5;
                }
                if (val_frac & 0x01) {
                    ret += 0.25;
                }
            } else {
                if (val_frac & 0x80) {
                    ret += 0.5;
                }
            }
        }
        return ret;
    }

    string name() override { return info_.name; }

    NuvotonTempSource GetSource() override {
        uint8_t source;
        chip_->ReadByte(info_.select, &source);
        return (NuvotonTempSource)(source & 0x1f);
    }

    Status SetSource(NuvotonTempSource target) override {
        uint8_t source;
        chip_->ReadByte(info_.select, &source);
        source = (source & ~0x1f) | target;
        return chip_->WriteByte(info_.select, source);
    }

    bool invalid() {
        return fabs(value()) < 1e-7 || fabs(value() - 255) < 1e-7;
    }

    void DumpInfo(std::ostream& out) override {
        if (invalid()) return;
        out << "Temp " << name() << " at " << value() << std::endl;
        if (info_.can_select) {
            out << "    source: " << GetSourceName(GetSource()) << std::endl;
        }
    }

   private:
    NuvotonTempInfo info_;
    NuvotonChip* chip_;
};

std::unique_ptr<NuvotonTempSensor> CreateNuvotonTempSensor(
    const NuvotonTempInfo& info, NuvotonChip* chip) {
    return std::make_unique<NuvotonTempSensorImpl>(info, chip);
}
