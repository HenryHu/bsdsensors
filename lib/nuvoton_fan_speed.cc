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
            return value_by_rpm();
        } else {
            return value_by_count();
        }
    }

    std::string name() const override { return info_.name; }

    void DumpInfo(std::ostream& out) override {
        out << "Fan " << name() << " at " << value() << std::endl;
        if (info_.rpm_high.valid) {
            out << "\tRPM: " << value_by_rpm() << std::endl;
        }
        if (info_.count.valid) {
            out << "\tRPM (count): " << value_by_count() << std::endl;
        }
    }

   private:
    double value_by_rpm() const {
        uint8_t high, low;
        chip_->ReadByte(info_.rpm_high, &high);
        chip_->ReadByte(info_.rpm_low, &low);
        return Combine(high, low);
    }

    double value_by_count() const {
        uint8_t count, divisor;
        chip_->ReadByte(info_.count, &count);
        if (info_.divisor.valid) {
            chip_->ReadByte(info_.divisor, &divisor);
        } else {
            divisor = 0;
        }
        // From 0~7 to 1~2^7=128
        divisor = 1 << divisor;
        return kCountDividend / count / divisor;
    }

    NuvotonFanInfo info_;
    NuvotonChip* chip_;
};

std::unique_ptr<NuvotonFanSpeed> CreateNuvotonFanSpeed(
    const NuvotonFanInfo& info, NuvotonChip* chip) {
    return std::make_unique<NuvotonFanSpeedImpl>(info, chip);
}

}  // namespace bsdsensors
