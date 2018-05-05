/*
 * fintek_fan.cc
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "fintek_fan.h"

namespace bsdsensors {

class FintekFanImpl : public FintekFan {
   public:
    FintekFanImpl(const FintekFanInfo& info, FintekChip* chip)
        : info_(info), chip_(chip) {}

    double value() const override {
        uint8_t high, low;
        chip_->ReadByte(info_.count_high, &high);
        chip_->ReadByte(info_.count_low, &low);
        return Combine(high, low);
    }

    std::string name() const override { return info_.name; }

    void DumpInfo(std::ostream& out) override {
        out << "Fan " << name() << " at " << value() << std::endl;
        out << "    at " << std::dec << (int)(current_percent() * 100) << "%"
            << std::endl;
    }

    double current_percent() const override {
        uint8_t duty;
        chip_->ReadByte(info_.duty, &duty);
        return duty / 255.0;
    }

   private:
    const FintekFanInfo& info_;
    FintekChip* chip_;
};

std::unique_ptr<FintekFan> CreateFintekFan(const FintekFanInfo& info,
                                           FintekChip* chip) {
    return std::make_unique<FintekFanImpl>(info, chip);
}

}  // namespace bsdsensors
