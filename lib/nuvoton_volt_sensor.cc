/*
 * nuvoton_volt_sensor.cc
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "nuvoton_volt_sensor.h"

namespace bsdsensors {

using std::string;

const double kVoltUnit = 0.008;  // 1 = 8mV

class NuvotonVoltSensorImpl : public NuvotonVoltSensor {
   public:
    NuvotonVoltSensorImpl(const NuvotonVoltInfo& info, NuvotonChip* chip)
        : info_(info), chip_(chip) {}

    double value() override {
        uint8_t value;
        chip_->ReadByte(info_.addr, &value);
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
    NuvotonVoltInfo info_;
    NuvotonChip* chip_;
};

std::unique_ptr<NuvotonVoltSensor> CreateNuvotonVoltSensor(
    const NuvotonVoltInfo& info, NuvotonChip* chip) {
    return std::make_unique<NuvotonVoltSensorImpl>(info, chip);
}

}  // namespace bsdsensors
