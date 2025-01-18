/*
 * nuvoton_fan_control.cc
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "nuvoton_fan_control.h"

#include <iostream>

namespace bsdsensors {
namespace {

using nuvoton::SmartFanIVRequest;
using std::string;

const uint8_t kInvalidControlTemp = 128;

double PowerToPercent(int power) { return 1.0 * power / 255 * 100.0; }

uint8_t PercentToPower(int percent) {
    int power = percent / 100.0 * 255;
    if (power >= 255) {
        return 255;
    } else {
        return power;
    }
}

std::string GetControlModeName(const NuvotonFanControlMode mode) {
    switch (mode) {
        case NuvotonFanControlMode::kManualMode: return "Manual";
        case NuvotonFanControlMode::kThermalCruise: return "Thermal Cruise";
        case NuvotonFanControlMode::kSpeedCruise: return "Speed Cruise";
        case NuvotonFanControlMode::kSmartFan4: return "SmartFanIV";
    }
    return "Unknown: " + std::to_string((int)mode);
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

class NuvotonFanControlThermalCruiseImpl
    : public NuvotonFanControlThermalCruise {
   public:
    NuvotonFanControlThermalCruiseImpl(const NuvotonThermalCruiseInfo& info,
                                       NuvotonChip* chip)
        : info_(info), chip_(chip) {}
    string name() const override { return "Thermal Cruise"; };

    Status Observe() override {
        RETURN_IF_ERROR(chip_->ReadByte(info_.target_temp, &target_temp));
        RETURN_IF_ERROR(chip_->ReadByte(info_.tolerance, &tolerance));
        RETURN_IF_ERROR(chip_->ReadByte(info_.start_value, &start_value));
        RETURN_IF_ERROR(chip_->ReadByte(info_.stop_value, &stop_value));
        RETURN_IF_ERROR(chip_->ReadByte(info_.keep_min_output, &keep_min_output));
        RETURN_IF_ERROR(chip_->ReadByte(info_.stop_time, &stop_time));
        RETURN_IF_ERROR(chip_->ReadByte(info_.step_up_time, &step_up_time));
        RETURN_IF_ERROR(chip_->ReadByte(info_.step_down_time, &step_down_time));
        RETURN_IF_ERROR(chip_->ReadByte(info_.critical_temp, &critical_temp));
        return OkStatus();
    }

    Status Apply() override {
        RETURN_IF_ERROR(chip_->WriteByte(info_.target_temp, target_temp));
        RETURN_IF_ERROR(chip_->WriteByte(info_.tolerance, tolerance));
        RETURN_IF_ERROR(chip_->WriteByte(info_.start_value, start_value));
        RETURN_IF_ERROR(chip_->WriteByte(info_.stop_value, stop_value));
        RETURN_IF_ERROR(chip_->WriteByte(info_.keep_min_output, keep_min_output));
        RETURN_IF_ERROR(chip_->WriteByte(info_.stop_time, stop_time));
        RETURN_IF_ERROR(chip_->WriteByte(info_.step_up_time, step_up_time));
        RETURN_IF_ERROR(chip_->WriteByte(info_.step_down_time, step_down_time));
        RETURN_IF_ERROR(chip_->WriteByte(info_.critical_temp, critical_temp));
        return OkStatus();
    }

    void DumpInfo(std::ostream& out) override {
        Observe();
        out << "      Thermal Cruise: ";
        out << "Target: " << target_temp << " C";
    }

    void FillState(FanControlMethodProto* proto) override {
        Observe();
        nuvoton::FanControlMethod* method = proto->mutable_nuvoton_method();
        nuvoton::ThermalCruiseParams* params =
            method->mutable_thermal_cruise_params();
        params->set_target_temp(target_temp);
        params->set_tolerance(tolerance);
        params->set_start_value(start_value);
        params->set_stop_value(stop_value);
        params->set_keep_min_output(keep_min_output);
        params->set_stop_time(stop_time);
        params->set_step_up_time(step_up_time);
        params->set_step_down_time(step_down_time);
        params->set_critical_temp(critical_temp);
    }

   private:
    uint8_t target_temp, tolerance, start_value, stop_value;
    uint8_t keep_min_output, stop_time, step_up_time, step_down_time, critical_temp;
    NuvotonThermalCruiseInfo info_;
    NuvotonChip* chip_;
};

std::ostream& operator<<(std::ostream& out,
                         const nuvoton::ThermalCruiseParams& params) {
    out << "    Target temp: " << params.target_temp() << "C" << " "
        << "Tolerance: " << params.tolerance() << "C" << " "
        << "Start value: " << params.start_value() << " Stop value: " << params.stop_value() << " "
        << "Keep min output: " << params.keep_min_output() << std::endl;
    out << "    Stop time: " << params.stop_time()
        << " Step up time: " << params.step_up_time() << " " << "Step down time: " << params.step_down_time()
        << " Critical temp: " << params.critical_temp() << "C" << std::endl;
    return out;
}

class NuvotonFanControlSpeedCruiseImpl : public NuvotonFanControlSpeedCruise {
   public:
    NuvotonFanControlSpeedCruiseImpl(const NuvotonSpeedCruiseInfo& info,
                                       NuvotonChip* chip)
        : info_(info), chip_(chip) {}
    string name() const override { return "Speed Cruise"; };

    Status Observe() override {
        RETURN_IF_ERROR(chip_->ReadByte(info_.target_speed_count_low,
                    &target_speed_count_low_));
        RETURN_IF_ERROR(chip_->ReadByte(info_.target_speed_count_high,
                    &target_speed_count_high_));
        RETURN_IF_ERROR(chip_->ReadByte(info_.tolerance_low,
                    &tolerance_low_));
        RETURN_IF_ERROR(chip_->ReadByte(info_.tolerance_high,
                    &tolerance_high_));
        RETURN_IF_ERROR(chip_->ReadByte(info_.step_up_time,
                    &step_up_time_));
        RETURN_IF_ERROR(chip_->ReadByte(info_.step_down_time,
                    &step_down_time_));
        RETURN_IF_ERROR(chip_->ReadByte(info_.step_up_value,
                    &step_up_value_));
        RETURN_IF_ERROR(chip_->ReadByte(info_.step_down_value,
                    &step_down_value_));
        return OkStatus();
    }

    Status Apply() override {
        RETURN_IF_ERROR(chip_->WriteByte(info_.target_speed_count_low,
                    target_speed_count_low_));
        RETURN_IF_ERROR(chip_->WriteByte(info_.target_speed_count_high,
                    target_speed_count_high_));
        RETURN_IF_ERROR(chip_->WriteByte(info_.tolerance_low,
                    tolerance_low_));
        RETURN_IF_ERROR(chip_->WriteByte(info_.tolerance_high,
                    tolerance_high_));
        RETURN_IF_ERROR(chip_->WriteByte(info_.step_up_time,
                    step_up_time_));
        RETURN_IF_ERROR(chip_->WriteByte(info_.step_down_time,
                    step_down_time_));
        RETURN_IF_ERROR(chip_->WriteByte(info_.step_up_value,
                    step_up_value_));
        RETURN_IF_ERROR(chip_->WriteByte(info_.step_down_value,
                    step_down_value_));
        return OkStatus();
    }

    void DumpInfo(std::ostream& out) override {
        Observe();
        out << "      Speed Cruise: " << std::endl;
        out << "Target speed count: " << Combine(target_speed_count_high_, target_speed_count_low_) << std::endl;
        out << "Tolerance: " << Combine(tolerance_high_, tolerance_low_) << std::endl;
        out << "Step up - time: " << step_up_time_ << " value: " << step_up_value_ << std::endl;
        out << "Step down - time: " << step_down_time_ << " value: " << step_down_value_ << std::endl;
    }

    void FillState(FanControlMethodProto* proto) override {
        Observe();
        nuvoton::FanControlMethod* method = proto->mutable_nuvoton_method();
        nuvoton::SpeedCruiseParams& params =
            *method->mutable_speed_cruise_params();
        params.set_target_speed_count_high(target_speed_count_high_);
        params.set_target_speed_count_low(target_speed_count_low_);
        params.set_tolerance_high(tolerance_high_);
        params.set_tolerance_low(tolerance_low_);
        params.set_step_up_time(step_up_time_);
        params.set_step_down_time(step_down_time_);
        params.set_step_up_value(step_up_value_);
        params.set_step_down_value(step_down_value_);
    }

   private:
    NuvotonSpeedCruiseInfo info_;
    NuvotonChip* chip_;

    uint8_t target_speed_count_low_, target_speed_count_high_;
    uint8_t tolerance_low_, tolerance_high_;
    uint8_t step_up_time_, step_down_time_;
    uint8_t step_up_value_, step_down_value_;
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
            default: {
                return Status(ENOSYS, "Unknown request");
            }
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

class DummyNuvotonFanControlImpl : public NuvotonFanControl {
   public:
    Status SetControlMode(NuvotonFanControlMode target) override {
        return Status(EINVAL, "No fan control");
    }
    Status SetControlMode(const std::string& target) override {
        return Status(EINVAL, "No fan control");
    }
    Status SetTempSource(const std::string& name) override {
        return Status(EINVAL, "No fan control");
    }
    Status GetCurrentMethod(FanControlMethod** method) override {
        *method = &dummy_method_;
        return OkStatus();
    }
    void FillState(FanControlProto* proto) override {}
    Status HandleRequest(const FanControlRequest& request) override {
        return Status(EINVAL, "No fan control");
    }
    void DumpInfo(std::ostream& out) override {}
    double current_percent() const override { return 1.0; }

   private:
    class DummyNuvotonFanControlMethod : public FanControlMethod {
        std::string name() const override { return "Dummy"; }
        Status Observe() override { return OkStatus(); }
        Status Apply() override { return OkStatus(); }
        void DumpInfo(std::ostream& out) override {}
        void FillState(FanControlMethodProto* proto) override {}
    };
    DummyNuvotonFanControlMethod dummy_method_;
};

class NuvotonFanControlImpl : public NuvotonFanControl {
   public:
    NuvotonFanControlImpl(const NuvotonFanControlInfo& info,
            const NuvotonTempSourceTable& temp_source_table, NuvotonChip* chip)
        : info_(info), temp_source_table_(temp_source_table), chip_(chip) {
        manual_ = std::make_unique<NuvotonFanControlManualImpl>(
            info.output_value_write, chip);
        if (info.smart_fan.available) {
            thermal_ = std::make_unique<NuvotonFanControlThermalCruiseImpl>(
                info.smart_fan.thermal_cruise, chip);
            speed_ = std::make_unique<NuvotonFanControlSpeedCruiseImpl>(
                info.smart_fan.speed_cruise, chip);
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
        return chip_->WriteByte(info_.mode_select, (int)target);
    }

    Status SetControlMode(const std::string& target) override {
        NuvotonFanControlMode mode;
        RETURN_IF_ERROR(ParseNuvotonFanControlMode(target, &mode));
        return SetControlMode(mode);
    }

    Status GetCurrentMethod(FanControlMethod** method) override {
        NuvotonFanControlMode mode = GetControlMode();
        switch (mode) {
            case NuvotonFanControlMode::kManualMode: {
                *method = manual_.get();
                break;
            }
            case NuvotonFanControlMode::kThermalCruise: {
                *method = thermal_.get();
                break;
            }
            case NuvotonFanControlMode::kSpeedCruise: {
                *method = speed_.get();
                break;
            }
            case NuvotonFanControlMode::kSmartFan4: {
                *method = iv_.get();
                break;
            }
            default: {
                return Status(EINVAL, "Unknown fan control mode: " +
                                          std::to_string(int(mode)));
            }
        }
        return OkStatus();
    }

    NuvotonTempSource GetTempSourceById(const uint8_t source_id) {
        for (const auto& [source, id] : temp_source_table_) {
            if (id == source_id) return source;
        }
        LOG(ERROR) << "Can't find temp source with ID: " << (int)source_id;
        return (NuvotonTempSource)source_id;
    }

    uint8_t GetTempSourceId(const NuvotonTempSource source) {
        const auto id_iter = temp_source_table_.find(source);
        if (id_iter == temp_source_table_.end()) {
            LOG(ERROR) << "Temp source " << GetNuvotonSourceName(source)
                << " does not exist for this chip.";
            return (uint8_t)source;
        }
        return id_iter->second;
    }

    NuvotonTempSource GetTempSource() {
        uint8_t source;
        chip_->ReadByte(info_.temp_source, &source);
        return GetTempSourceById(source);
    }

    Status SetTempSource(NuvotonTempSource source) {
        return chip_->WriteByte(info_.temp_source, GetTempSourceId(source));
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
        if (source == NuvotonTempSource::kSourceUnknown) {
            return Status(EINVAL, "Invalid temp source name " + name);
        } else {
            return SetTempSource(source);
        }
    }

    void DumpInfo(std::ostream& out) override {
        out << "    at " << std::dec << (int)(current_percent() * 100) << "%"
            << " with ";
        out << GetControlModeName(GetControlMode()) << std::endl;
        out << "    temp source: " << GetNuvotonSourceName(GetTempSource())
            << " value: " << GetTempValue() << std::endl;
        out << "    control:";
        out << " Manual";
        if (thermal_) out << " ThermalCruise";
        if (speed_) out << " SpeedCruise";
        if (iv_) out << " SmartFanIV";
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
            manual_->FillState(method);
        }
        if (thermal_) {
            FanControlMethodProto* method = proto->add_methods();
            method->set_name(thermal_->name());
            thermal_->FillState(method);
        }
        if (speed_) {
            FanControlMethodProto* method = proto->add_methods();
            method->set_name(speed_->name());
            speed_->FillState(method);
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
                    default: {
                        return Status(ENOSYS, "Request not supported");
                    }
                }
            }
            default: {
                return Status(ENOSYS, "Request not supported");
            }
        }
    }

   private:
    NuvotonFanControlInfo info_;
    NuvotonTempSourceTable temp_source_table_;
    NuvotonChip* chip_;
    std::unique_ptr<NuvotonFanControlManual> manual_;
    std::unique_ptr<NuvotonFanControlThermalCruise> thermal_;
    std::unique_ptr<NuvotonFanControlSpeedCruise> speed_;
    std::unique_ptr<NuvotonFanControlSmartFan4> iv_;
};

std::unique_ptr<NuvotonFanControl> CreateNuvotonFanControl(
    const NuvotonFanControlInfo& info, const NuvotonTempSourceTable& table,
    NuvotonChip* chip) {
    return std::make_unique<NuvotonFanControlImpl>(info, table, chip);
}

std::unique_ptr<NuvotonFanControl> CreateDummyNuvotonFanControl() {
    return std::make_unique<DummyNuvotonFanControlImpl>();
}

std::ostream& operator<<(std::ostream& out,
                         const nuvoton::SpeedCruiseParams& params) {
    out << "    Target speed count: " << Combine(params.target_speed_count_high(), params.target_speed_count_low()) << std::endl;
    out << "    Tolerance: " << Combine(params.tolerance_high(), params.tolerance_low()) << std::endl;
    out << "    Step up - time: " << params.step_up_time() << " value: " << params.step_up_value() << std::endl;
    out << "    Step down - time: " << params.step_down_time() << " value: " << params.step_down_value() << std::endl;
    return out;
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
        case nuvoton::FanControlMethod::kThermalCruiseParams: {
            out << method.thermal_cruise_params();
            break;
        }
        case nuvoton::FanControlMethod::kSpeedCruiseParams: {
            out << method.speed_cruise_params();
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
        *mode = NuvotonFanControlMode::kManualMode;
        return OkStatus();
    }
    if (str_mode == "SmartFan IV") {
        *mode = NuvotonFanControlMode::kSmartFan4;
        return OkStatus();
    }
    return Status(EINVAL, "Unknown mode " + str_mode);
}

}  // namespace bsdsensors
