/*
 * nuvoton_fan_control.cc
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "nuvoton_fan_control.h"

class NuvotonFanControlImpl : public NuvotonFanControl {
   public:
    NuvotonFanControlImpl(const NuvotonFanControlInfo& info, NuvotonChip* chip)
        : info_(info), chip_(chip) {}

    double current_percent() override {
        uint8_t value;
        double ret;
        chip_->ReadByte(info_.output_value_read, &value);
        ret = 1.0 * value / 255.0;
        return ret;
    }

   private:
    NuvotonFanControlInfo info_;
    NuvotonChip* chip_;
};

std::unique_ptr<NuvotonFanControl> CreateNuvotonFanControl(
    const NuvotonFanControlInfo& info, NuvotonChip* chip) {
    return std::make_unique<NuvotonFanControlImpl>(info, chip);
}
