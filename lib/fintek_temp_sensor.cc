/*
 * fintek_temp_sensor.cc
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "fintek_temp_sensor.h"

#include <cmath>

namespace bsdsensors {

class FintekTempSensorImpl : public FintekTempSensor {
   public:
    FintekTempSensorImpl(const FintekTempInfo& info, FintekChip* chip)
        : info_(info), chip_(chip) {}

    double value() override {
        uint8_t val_int;
        chip_->ReadByte(info_.value, &val_int);
        double ret = val_int;
        if (info_.value_frac.valid) {
            uint8_t val_frac;
            chip_->ReadByte(info_.value_frac, &val_frac);
            if (val_frac) {
                ret += 0.5;
            }
        }
        return ret;
    }

    std::string name() override { return info_.name; }

    bool invalid() {
        return fabs(value()) < 1e-7 || fabs(value() - 255) < 1e-7;
    }

    void DumpInfo(std::ostream& out) override {
        if (invalid()) return;
        out << "Temp " << name() << " at " << value() << std::endl;
    }

   private:
    FintekTempInfo info_;
    FintekChip* chip_;
};

std::unique_ptr<FintekTempSensor> CreateFintekTempSensor(
    const FintekTempInfo& info, FintekChip* chip) {
    return std::make_unique<FintekTempSensorImpl>(info, chip);
}

}  // namespace bsdsensors
