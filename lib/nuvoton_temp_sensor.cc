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
