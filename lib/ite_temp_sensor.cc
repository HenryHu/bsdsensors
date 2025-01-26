/*
 * ite_temp_sensor.cc
 * Copyright (C) 2025 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "ite_temp_sensor.h"

namespace bsdsensors {

class ITETempSensorImpl : public ITETempSensor {
  public:
    ITETempSensorImpl(const ITETempInfo& info, ITEChip* chip)
      : info_(info), chip_(*chip) {}
    virtual ~ITETempSensorImpl() {}

    double value() override {
        uint8_t data;
        if (!chip_.ReadByte(info_.value, &data).ok()) {
            LOG(ERROR) << "fail to read temp data";
            return 0;
        }
        return (int8_t)data;
    }

    std::string name() override {
        return info_.name;
    }

    void DumpInfo(std::ostream& out) override {
        out << "Temperature of " << name() << ": " << value() << "V" << std::endl;
    }

  private:
    const ITETempInfo info_;
    ITEChip& chip_;
};

std::unique_ptr<ITETempSensor> CreateITETempSensor(
    const ITETempInfo& info, ITEChip* chip) {
    return std::make_unique<ITETempSensorImpl>(info, chip);
}
}

