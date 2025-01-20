/*
 * nuvoton_volt_sensor.cc
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "nuvoton_volt_sensor.h"

namespace bsdsensors {

using std::string;

class NuvotonVoltSensorImpl : public NuvotonVoltSensor {
   public:
    NuvotonVoltSensorImpl(const NuvotonVoltInfo& info, const double volt_unit,
            NuvotonChip* chip)
        : info_(info), volt_unit_(volt_unit), chip_(chip) {}

    double value() override {
        uint8_t value;
        chip_->ReadByte(info_.addr, &value);
        double ret;
        ret = value * volt_unit_;

        ret = ret * info_.alpha + info_.beta;
        return ret;
    }

    string name() override { return info_.name; }

    void DumpInfo(std::ostream& out) override {
        out << "Volt " << name() << " at " << value() << std::endl;
    }

   private:
    NuvotonVoltInfo info_;
    const double volt_unit_;
    NuvotonChip* chip_;
};

std::unique_ptr<NuvotonVoltSensor> CreateNuvotonVoltSensor(
    const NuvotonVoltInfo& info, const double volt_unit, NuvotonChip* chip) {
    return std::make_unique<NuvotonVoltSensorImpl>(info, volt_unit, chip);
}

}  // namespace bsdsensors
