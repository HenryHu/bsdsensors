/*
 * ite_volt_sensor.cc
 * Copyright (C) 2025 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "ite_volt_sensor.h"

namespace bsdsensors {

class ITEVoltSensorImpl : public ITEVoltSensor {
  public:
    ITEVoltSensorImpl(const ITEVoltInfo& info, ITEChip* chip)
      : info_(info), chip_(*chip) {}
    virtual ~ITEVoltSensorImpl() {}

    double value() override {
        uint8_t data;
        if (!chip_.ReadByte(info_.value, &data).ok()) {
            LOG(ERROR) << "fail to read volt data";
            return 0;
        }
        return data * 0.012 * info_.alpha + info_.beta;
    }

    std::string name() override {
        return info_.name;
    }

    void DumpInfo(std::ostream& out) override {
        out << "Voltage of " << name() << ": " << value() << "V" << std::endl;
    }

  private:
    const ITEVoltInfo info_;
    ITEChip& chip_;
};

std::unique_ptr<ITEVoltSensor> CreateITEVoltSensor(
    const ITEVoltInfo& info, ITEChip* chip) {
    return std::make_unique<ITEVoltSensorImpl>(info, chip);
}
}
