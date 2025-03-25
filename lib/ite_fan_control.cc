/*
 * ite_fan_control.cc
 * Copyright (C) 2025 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "ite_fan_control.h"

#include <iostream>

#include "ite_chip_info.h"

namespace bsdsensors {
namespace {

std::string GetControlModeName(const ITEFanControlMode mode) {
    switch (mode) {
        case ITEFanControlMode::kSoftwareOperation:
            return "Software operation";
        case ITEFanControlMode::kAutomaticOperation:
            return "Automatic operation";
    }
    return "Unknown";
}

}

class ITEFanControlImpl : public ITEFanControl {
  public:
      ITEFanControlImpl(const ITEFanControlInfo& info, ITEChip* chip)
          : info_(info), chip_(chip) {}

    double current_percent() const override {
        ITEFanControlMode mode;
        Status status = GetControlMode(mode);
        if (!status.ok()) {
            LOG(ERROR) << status;
            return 1.0;
        }
        switch (mode) {
            case ITEFanControlMode::kSoftwareOperation: {
                uint8_t pwm;
                status = GetPWM(pwm);
                if (!status.ok()) {
                    LOG(ERROR) << status;
                    return 1.0;
                }
                return (double)pwm / 255;
            }
            case ITEFanControlMode::kAutomaticOperation: {
                // We don't really have a value to return here.
                return 1.0;
            }
        }
    }

    void DumpInfo(std::ostream& out) override {
        ITEFanControlMode mode;
        RETURN_VOID_IF_ERROR(GetControlMode(mode));
        out << "Fan Control " << info_.name << std::endl;
        out << "  Mode: " << GetControlModeName(mode) << std::endl;
        switch (mode) {
            case ITEFanControlMode::kSoftwareOperation: {
                uint8_t pwm;
                RETURN_VOID_IF_ERROR(GetPWM(pwm));
                out << "  PWM: " << (int)pwm << " / 255" << std::endl;
                break;
            }
            case ITEFanControlMode::kAutomaticOperation: {
                std::string temp_source;
                RETURN_VOID_IF_ERROR(GetTempSource(temp_source));
                out << "  Temp source: " << temp_source << std::endl;
                break;
            }
        }
    }

    std::string name() override { return info_.name; }

    Status GetSensorValues(FanControlProto& proto) override {
        ITEFanControlMode mode;
        RETURN_IF_ERROR(GetControlMode(mode));
        proto.set_current_method(GetControlModeName(mode));
        switch (mode) {
            case ITEFanControlMode::kSoftwareOperation: {
                uint8_t pwm;
                RETURN_IF_ERROR(GetPWM(pwm));
                proto.set_current_percent((double)pwm / 255);
                break;
            }
            case ITEFanControlMode::kAutomaticOperation: {
                std::string temp_source;
                RETURN_IF_ERROR(GetTempSource(temp_source));
                proto.set_temp_source(temp_source);
                break;
            }
        }
        return OkStatus();
    }

  private:
    Status GetControlMode(ITEFanControlMode& mode) const {
        if (!info_.mode_select.valid) {
            mode = ITEFanControlMode::kSoftwareOperation;
            return OkStatus();
        }
        uint8_t result;
        RETURN_IF_ERROR(chip_->ReadByte(info_.mode_select, &result));
        mode = (ITEFanControlMode)result;
        return OkStatus();
    }

    Status GetPWM(uint8_t& pwm) const {
        ITEFanControlMode mode;
        RETURN_IF_ERROR(GetControlMode(mode));
        if (mode != ITEFanControlMode::kSoftwareOperation) {
            return Status(EINVAL, "Not in software operation mode");
        }
        return chip_->ReadByte(info_.pwm, &pwm);
    }

    Status GetTempSource(std::string& temp_source) {
        ITEFanControlMode mode;
        RETURN_IF_ERROR(GetControlMode(mode));
        if (mode != ITEFanControlMode::kAutomaticOperation) {
            return Status(EINVAL, "Not in automatic operation mode");
        }
        uint8_t temp_source_byte;
        RETURN_IF_ERROR(chip_->ReadByte(info_.temp_input_select, &temp_source_byte));
        const auto it = info_.temp_inputs.find(temp_source_byte);
        if (it == info_.temp_inputs.end()) {
            return Status(EINVAL, "Unknown temp source: " +
                          std::to_string((int)temp_source_byte));
        }
        temp_source = it->second;
        return OkStatus();
    }

    const ITEFanControlInfo info_;
    ITEChip* chip_;
};

std::unique_ptr<ITEFanControl> CreateITEFanControl(const ITEFanControlInfo& info, ITEChip* chip) {
    return std::make_unique<ITEFanControlImpl>(info, chip);
}

}
