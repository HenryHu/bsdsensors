/*
 * nuvoton_fan_speed.cc
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "nuvoton_fan_speed.h"
#include "util.h"

namespace bsdsensors {

const int kCountDividend = 1.35e6;

class NuvotonFanSpeedImpl : public NuvotonFanSpeed {
   public:
    NuvotonFanSpeedImpl(const NuvotonFanInfo& info, NuvotonChip* chip)
        : info_(info), chip_(chip) {}

    double value() const override {
        if (info_.rpm_high.valid) {
            uint8_t high, low;
            chip_->ReadByte(info_.rpm_high, &high);
            chip_->ReadByte(info_.rpm_low, &low);
            return Combine(high, low);
        } else {
            uint8_t count, divisor;
            chip_->ReadByte(info_.count, &count);
            chip_->ReadByte(info_.divisor, &divisor);
            // From 0~7 to 1~2^7=128
            divisor = 1 << divisor;
            return kCountDividend / count / divisor;
        }
    }

    std::string name() const override { return info_.name; }

    void DumpInfo(std::ostream& out) override {
        out << "Fan " << name() << " at " << value() << std::endl;
    }

   private:
    NuvotonFanInfo info_;
    NuvotonChip* chip_;
};

std::unique_ptr<NuvotonFanSpeed> CreateNuvotonFanSpeed(
    const NuvotonFanInfo& info, NuvotonChip* chip) {
    return std::make_unique<NuvotonFanSpeedImpl>(info, chip);
}

}  // namespace bsdsensors
