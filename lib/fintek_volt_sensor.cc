/*
 * fintek_volt_sensor.cc
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "fintek_volt_sensor.h"

namespace bsdsensors {

using std::string;

const double kVoltUnit = 0.008;  // 1 = 8mV

class FintekVoltSensorImpl : public FintekVoltSensor {
   public:
    FintekVoltSensorImpl(const FintekVoltInfo& info, FintekChip* chip)
        : info_(info), chip_(chip) {}

    double value() override {
        uint8_t value;
        chip_->ReadByte(info_.value, &value);
        double ret;
        ret = value * kVoltUnit;

        ret = ret * info_.alpha + info_.beta;
        return ret;
    }

    string name() override { return info_.name; }

    void DumpInfo(std::ostream& out) override {
        out << "Volt " << name() << " at " << value() << std::endl;
    }

   private:
    FintekVoltInfo info_;
    FintekChip* chip_;
};

std::unique_ptr<FintekVoltSensor> CreateFintekVoltSensor(
    const FintekVoltInfo& info, FintekChip* chip) {
    return std::make_unique<FintekVoltSensorImpl>(info, chip);
}

}  // namespace bsdsensors
