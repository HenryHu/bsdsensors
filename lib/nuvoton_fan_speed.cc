/*
 * nuvoton_fan_speed.cc
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "nuvoton_fan_speed.h"
#include "util.h"

namespace bsdsensors {

class NuvotonFanSpeedImpl : public NuvotonFanSpeed {
   public:
    NuvotonFanSpeedImpl(const NuvotonFanInfo& info, NuvotonChip* chip)
        : info_(info), chip_(chip) {}

    double value() const override {
        uint8_t high, low;
        chip_->ReadByte(info_.rpm_high, &high);
        chip_->ReadByte(info_.rpm_low, &low);
        return Combine(high, low);
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
