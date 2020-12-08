/*
 * nuvoton_fan_control.cc
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "nuvoton_fan_control.h"
#include <iostream>

namespace bsdsensors {

using nuvoton::SmartFanIVRequest;
using std::string;

const uint8_t kInvalidControlTemp = 128;

static double PowerToPercent(int power) { return 1.0 * power / 255 * 100.0; }

static uint8_t PercentToPower(int percent) {
    int power = percent / 100.0 * 255;
    if (power >= 255) {
        return 255;
    } else {
        return power;
    }
}

class NuvotonFanControlManualImpl : public NuvotonFanControlManual {
   public:
    NuvotonFanControlManualImpl(const NuvotonChip::AddressType& control_addr,
                                NuvotonChip* chip)
        : control_addr_(control_addr), chip_(chip) {}
    string name() const override { return "Manual"; }
    Status Observe() override { return chip_->ReadByte(control_addr_, &power); }
    Status Apply() override { return chip_->WriteByte(control_addr_, power); }
    void DumpInfo(std::ostream& out) override {}
    Status SetPower(int percent) override {
        power = PercentToPower(percent);
        return Apply();
    }

    void FillState(FanControlMethodProto* proto) override {
        proto->mutable_nuvoton_method()->mutable_manual_params()->set_percent(
            PowerToPercent(power));
    }

   private:
    uint8_t power;

    NuvotonChip::AddressType control_addr_;
    NuvotonChip* chip_;
};

struct NuvotonFanControlSmartFan4ControlPoint {
    uint8_t temp;
    uint8_t power;
};

class NuvotonFanControlSmartFan4Impl : public NuvotonFanControlSmartFan4 {
   public:
    NuvotonFanControlSmartFan4Impl(const NuvotonSmartFan4Info& info,
                                   NuvotonChip* chip)
        : info_(info), chip_(chip) {}
    string name() const override { return "SmartFan IV"; };

    Status Observe() override {
        control_points_.clear();
        for (const auto& control_point : info_.control_points) {
            uint8_t temp, power;
            RETURN_IF_ERROR(chip_->ReadByte(control_point.temp, &temp));
            RETURN_IF_ERROR(chip_->ReadByte(control_point.power, &power));
            control_points_.push_back({temp, power});
        }
        return OkStatus();
    }

    Status Apply() override {
        for (int i = 0; i < info_.control_points.size(); i++) {
            const auto& control_point = info_.control_points[i];
            RETURN_IF_ERROR(
                chip_->WriteByte(control_point.temp, control_points_[i].temp));
            RETURN_IF_ERROR(chip_->WriteByte(control_point.power,
                                             control_points_[i].power));
        }

        return OkStatus();
    }

    void DumpInfo(std::ostream& out) override {
        Observe();
        out << "      SmartFanIV: ";
        bool first = true;
        for (const auto& control_point : control_points_) {
            if (!first) out << ", ";
            first = false;
            out << (int)control_point.temp << "C -> "
                << (int)PowerToPercent(control_point.power) << "%";
        }
        out << std::endl;
    }

    void FillState(FanControlMethodProto* proto) override {
        Observe();

        nuvoton::FanControlMethod* method = proto->mutable_nuvoton_method();
        nuvoton::SmartFanIVParams* params =
            method->mutable_smart_fan_iv_params();
        for (const auto& control_point : control_points_) {
            nuvoton::ControlPoint* point_proto = params->add_control_points();
            point_proto->set_temp(control_point.temp);
            point_proto->set_percent(PowerToPercent(control_point.power));
        }
    }

    Status HandleRequest(const SmartFanIVRequest& request) override {
        switch (request.request_case()) {
            case SmartFanIVRequest::kAddControlPoint: {
                return AddControlPoint(request.add_control_point().temp(),
                                       request.add_control_point().percent());
            }
            case SmartFanIVRequest::kDelControlPoint: {
                return DelControlPoint(request.del_control_point().temp());
            }
            default: { return Status(ENOSYS, "Unknown request"); }
        }
    }

   private:
    Status AddControlPoint(double temp, double percent) {
        LOG(INFO) << "Adding control point at " << temp << ": " << percent
                  << "%";

        Observe();
        for (auto& control_point : control_points_) {
            if ((uint8_t)temp == control_point.temp) {
                LOG(INFO) << "Found an existing control point.";
                control_point.power = PercentToPower(percent);
                return Apply();
            }
        }

        // No existing point, create a new one
        int free_count = 0;
        for (const auto& control_point : control_points_) {
            if (control_point.temp == kInvalidControlTemp) {
                free_count++;
            }
        }
        if (free_count == 0) {
            return Status(ENOSPC, "No free slot. Delete control points first.");
        }

        for (int i = 0; i < control_points_.size(); i++) {
            if (control_points_[i].temp > temp) {
                for (int j = control_points_.size() - 1; j > i; j--) {
                    control_points_[j] = control_points_[j - 1];
                }
                control_points_[i].temp = temp;
                control_points_[i].power = PercentToPower(percent);
                return Apply();
            }
        }
        control_points_.rbegin()->temp = temp;
        control_points_.rbegin()->power = PercentToPower(percent);

        return Apply();
    }

    Status DelControlPoint(double temp) {
        LOG(INFO) << "Deleting control point at " << temp;
        RETURN_IF_ERROR(Observe());
        for (int i = 0; i < control_points_.size(); i++) {
            LOG(INFO) << (int)control_points_[i].temp;
            if ((uint8_t)temp == control_points_[i].temp) {
                for (int j = i + 1; j < info_.control_points.size(); j++) {
                    control_points_[j - 1] = control_points_[j];
                }
                control_points_.rbegin()->temp = kInvalidControlTemp;
                return Apply();
            }
        }
        return Status(ENOENT, "Control point not found");
    }

    std::vector<NuvotonFanControlSmartFan4ControlPoint> control_points_;
    NuvotonSmartFan4Info info_;
    NuvotonChip* chip_;
};

class NuvotonFanControlImpl : public NuvotonFanControl {
   public:
    NuvotonFanControlImpl(const NuvotonFanControlInfo& info, NuvotonChip* chip)
        : info_(info), chip_(chip) {
        manual_ = std::make_unique<NuvotonFanControlManualImpl>(
            info.output_value_write, chip);
        if (info.smart_fan.available) {
        }
        if (info.smart_fan4.available) {
            iv_ = std::make_unique<NuvotonFanControlSmartFan4Impl>(
                info.smart_fan4, chip);
        }
    }

    double current_percent() const override {
        uint8_t value;
        double ret;
        chip_->ReadByte(info_.output_value_read, &value);
        ret = value / 255.0;
        return ret;
    }

    NuvotonFanControlMode GetControlMode() {
        uint8_t mode;
        chip_->ReadByte(info_.mode_select, &mode);
        return (NuvotonFanControlMode)mode;
    }

    Status SetControlMode(NuvotonFanControlMode target) override {
        return chip_->WriteByte(info_.mode_select, target);
    }

    Status SetControlMode(const std::string& target) override {
        NuvotonFanControlMode mode;
        RETURN_IF_ERROR(ParseNuvotonFanControlMode(target, &mode));
        return SetControlMode(mode);
    }

    Status GetCurrentMethod(FanControlMethod** method) override {
        NuvotonFanControlMode mode = GetControlMode();
        switch (mode) {
            case kManualMode: {
                *method = manual_.get();
                break;
            }
            case kThermalCruise: {
                *method = thermal_.get();
                break;
            }
            case kSpeedCruise: {
                *method = speed_.get();
                break;
            }
            case kSmartFan4: {
                *method = iv_.get();
                break;
            }
            default: { return Status(EINVAL, "Unknown fan control mode: " + std::to_string(mode)); }
        }
        return OkStatus();
    }

    NuvotonTempSource GetTempSource() {
        uint8_t source;
        chip_->ReadByte(info_.temp_source, &source);
        return (NuvotonTempSource)source;
    }

    Status SetTempSource(NuvotonTempSource source) {
        return chip_->WriteByte(info_.temp_source, source);
    }

    double GetTempValue() {
        uint8_t int_part, frac_part;
        chip_->ReadByte(info_.temp_value_int, &int_part);
        chip_->ReadByte(info_.temp_value_frac, &frac_part);
        double ret = int_part;
        if (frac_part) ret += 0.5;
        return ret;
    }

    Status SetTempSource(const string& name) override {
        NuvotonTempSource source;
        RETURN_IF_ERROR(GetNuvotonSourceByName(name, &source));
        if (source == kSourceUnknown) {
            return Status(EINVAL, "Invalid temp source name " + name);
        } else {
            return SetTempSource(source);
        }
    }

    void DumpInfo(std::ostream& out) override {
        out << "    at " << std::dec << (int)(current_percent() * 100) << "%"
            << " with ";
        switch (GetControlMode()) {
            case kManualMode: {
                out << "Manual";
                break;
            }
            case kThermalCruise: {
                out << "ThermalCruise";
                break;
            }
            case kSpeedCruise: {
                out << "SpeedCruise";
                break;
            }
            case kSmartFan4: {
                out << "SmartFanIV";
                break;
            }
            default: {
                out << "Unknown: " << (int)GetControlMode();
                break;
            }
        }
        out << std::endl;
        out << "    temp source: " << GetNuvotonSourceName(GetTempSource())
            << " value: " << GetTempValue() << std::endl;
        out << "    control:";
        out << " Manual";
        if (iv_) {
            out << " SmartFanIV";
        }
        out << std::endl;
        if (iv_) {
            iv_->DumpInfo(out);
        }
    }

    void FillState(FanControlProto* proto) override {
        proto->set_current_percent(current_percent());
        proto->set_temp_source(GetNuvotonSourceName(GetTempSource()));
        proto->set_temp_value(GetTempValue());
        if (manual_) {
            FanControlMethodProto* method = proto->add_methods();
            method->set_name(manual_->name());
        }
        if (thermal_) {
            FanControlMethodProto* method = proto->add_methods();
            method->set_name(thermal_->name());
        }
        if (speed_) {
            FanControlMethodProto* method = proto->add_methods();
            method->set_name(speed_->name());
        }
        if (iv_) {
            FanControlMethodProto* method = proto->add_methods();
            method->set_name(iv_->name());
            iv_->FillState(method);
        }
    }

    Status HandleRequest(const FanControlRequest& request) override {
        switch (request.request_case()) {
            case FanControlRequest::kSetMethod: {
                const SetMethodRequest& req = request.set_method();
                LOG(INFO) << "Setting fan " << request.name()
                          << "'s control method to " << req.method();
                return SetControlMode(req.method());
            }
            case FanControlRequest::kSetTempSource: {
                const SetTempSourceRequest& req = request.set_temp_source();
                LOG(INFO) << "Setting fan " << request.name()
                          << "'s temp source to " << req.source();
                return SetTempSource(req.source());
            }
            case FanControlRequest::kNuvoton: {
                const nuvoton::FanControlRequest& req = request.nuvoton();

                switch (req.request_case()) {
                    case nuvoton::FanControlRequest::kManualChangePercent: {
                        return manual_->SetPower(
                            req.manual_change_percent().percent());
                    }
                    case nuvoton::FanControlRequest::kSmartFanIv: {
                        return iv_->HandleRequest(req.smart_fan_iv());
                    }
                    default: { return Status(ENOSYS, "Request not supported"); }
                }
            }
            default: { return Status(ENOSYS, "Request not supported"); }
        }
    }

   private:
    NuvotonFanControlInfo info_;
    NuvotonChip* chip_;
    std::unique_ptr<NuvotonFanControlManual> manual_;
    std::unique_ptr<NuvotonFanControlThermalCruise> thermal_;
    std::unique_ptr<NuvotonFanControlSpeedCruise> speed_;
    std::unique_ptr<NuvotonFanControlSmartFan4> iv_;
};

std::unique_ptr<NuvotonFanControl> CreateNuvotonFanControl(
    const NuvotonFanControlInfo& info, NuvotonChip* chip) {
    return std::make_unique<NuvotonFanControlImpl>(info, chip);
}

std::ostream& operator<<(std::ostream& out,
                         const nuvoton::SmartFanIVParams& params) {
    bool first = true;
    out << "    ";
    for (const auto& control_point : params.control_points()) {
        if (!first) out << ", ";
        first = false;
        out << (int)control_point.temp() << "C -> "
            << (int)control_point.percent() << "%";
    }
    out << std::endl;
    return out;
}

std::ostream& operator<<(std::ostream& out,
                         const nuvoton::FanControlMethod& method) {
    switch (method.params_case()) {
        case nuvoton::FanControlMethod::kManualParams: {
            break;
        }
        case nuvoton::FanControlMethod::kSmartFanIvParams: {
            out << method.smart_fan_iv_params();
            break;
        }
        case nuvoton::FanControlMethod::PARAMS_NOT_SET: {
            break;
        }
    }
    return out;
}

Status ParseNuvotonFanControlMode(const std::string& str_mode,
                                  NuvotonFanControlMode* mode) {
    if (str_mode == "Manual") {
        *mode = kManualMode;
        return OkStatus();
    }
    if (str_mode == "SmartFan IV") {
        *mode = kSmartFan4;
        return OkStatus();
    }
    return Status(EINVAL, "Unknown mode " + str_mode);
}

}  // namespace bsdsensors
