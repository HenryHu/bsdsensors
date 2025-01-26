/*
 * ite_fan_speed.cc
 * Copyright (C) 2025 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "ite_fan_speed.h"

namespace bsdsensors {

class ITEFanSpeedImpl : public ITEFanSpeed {
  public:
    ITEFanSpeedImpl(const ITEFanSpeedInfo info, ITEChip* chip)
      : info_(info), chip_(*chip) {}
    virtual ~ITEFanSpeedImpl() {}

    double value() const override {
        uint8_t count;
        if (!chip_.ReadByte(info_.count, &count).ok()) {
            LOG(ERROR) << "fail to read fan speed data";
            return 0;
        }
        return 1.35e6 / 2 / count;
    }

    std::string name() const override {
        return info_.name;
    }

    void DumpInfo(std::ostream& out) override {
        out << "Fan Speed of " << name() << ": " << value() << "RPM" << std::endl;
    }

  private:
    const ITEFanSpeedInfo info_;
    ITEChip& chip_;
};

std::unique_ptr<ITEFanSpeed> CreateITEFanSpeed(
    const ITEFanSpeedInfo& info, ITEChip* chip) {
    return std::make_unique<ITEFanSpeedImpl>(info, chip);
}
}


