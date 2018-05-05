/*
 * nuvoton_temp_sensor.cc
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "nuvoton_temp_sensor.h"

#include <cmath>

namespace bsdsensors {

using std::string;

string GetNuvotonSourceName(NuvotonTempSource source) {
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

class NuvotonTempSensorImpl : public NuvotonTempSensor {
   public:
    NuvotonTempSensorImpl(const NuvotonTempInfo& info,
                          const NuvotonTempSourceTable& table,
                          NuvotonChip* chip)
        : info_(info), table_(table), chip_(chip) {}

    double value() override {
        uint8_t val_int;
        chip_->ReadByte(info_.val_int, &val_int);
        double ret = val_int;
        if (info_.val_frac.valid) {
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
                if (val_frac) {
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
        for (const auto& entry : table_) {
            if (entry.second == source) {
                return entry.first;
            }
        }
        return (NuvotonTempSource)source;
    }

    Status SetSource(NuvotonTempSource target) override {
        auto entry = table_.find(target);
        if (entry != table_.end()) {
            return chip_->WriteByte(info_.select, entry->second);
        } else {
            return Status(EINVAL, "Unavailable temp source " +
                                      GetNuvotonSourceName(target));
        }
    }

    bool invalid() {
        return fabs(value()) < 1e-7 || fabs(value() - 255) < 1e-7;
    }

    void DumpInfo(std::ostream& out) override {
        if (invalid()) return;
        out << "Temp " << name() << " at " << value() << std::endl;
        if (info_.can_select) {
            out << "    source: " << GetNuvotonSourceName(GetSource())
                << std::endl;
        }
    }

   private:
    const NuvotonTempInfo& info_;
    const NuvotonTempSourceTable& table_;
    NuvotonChip* chip_;
};

std::unique_ptr<NuvotonTempSensor> CreateNuvotonTempSensor(
    const NuvotonTempInfo& info, const NuvotonTempSourceTable& table,
    NuvotonChip* chip) {
    return std::make_unique<NuvotonTempSensorImpl>(info, table, chip);
}

}  // namespace bsdsensors
