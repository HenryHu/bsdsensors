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
    NuvotonTempSensorImpl(const string& name) : name_(name) {}
    double value() override { return 0; }

    string name() override { return name_; }

   private:
    string name_;
};

std::unique_ptr<NuvotonTempSensor> CreateNuvotonTempSensor(
    const std::string& name) {
    return std::make_unique<NuvotonTempSensorImpl>(name);
}
