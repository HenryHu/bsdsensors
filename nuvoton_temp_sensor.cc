/*
 * nuvoton_temp_sensor.cc
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "nuvoton_temp_sensor.h"

using std::string;

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

   private:
    NuvotonTempInfo info_;
    NuvotonChip* chip_;
};

std::unique_ptr<NuvotonTempSensor> CreateNuvotonTempSensor(
    const NuvotonTempInfo& info, NuvotonChip* chip) {
    return std::make_unique<NuvotonTempSensorImpl>(info, chip);
}
