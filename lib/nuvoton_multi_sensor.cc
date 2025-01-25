/*
 * nuvoton_multi_sensor.cc
 * Copyright (C) 2025 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "nuvoton_chip_info.h"
#include "nuvoton_multi_sensor.h"

#include <memory>
#include <string>

namespace bsdsensors {

class NuvotonMultiSensorImpl : public NuvotonMultiSensor {
  public:
    NuvotonMultiSensorImpl(const NuvotonMultiSensorInfo& info,
            const NuvotonSensorSourceTable& table, NuvotonChip* chip)
        : info_(info), table_(table), chip_(chip) {}

    virtual ~NuvotonMultiSensorImpl() {}

    double value() override {
        const NuvotonSensorSourceInfo* source = GetSource();
        if (source == nullptr) return 0;
        switch (source->type) {
            case NuvotonSensorType::kTemp:
                {
                    uint8_t high, low;
                    if (!chip_->ReadByte(info_.value_high, &high).ok() ||
                        !chip_->ReadByte(info_.value_low, &low).ok()) {
                        return 0;
                    }
                    double value = high;
                    if (low) value += 0.5;
                    return value;
                }
            case NuvotonSensorType::kVolt:
                {
                    uint8_t value;
                    if (!chip_->ReadByte(info_.value_high, &value).ok()) {
                        return 0;
                    }
                    return value * 0.016;
                }
        }
        LOG(ERROR) << "Unknown sensor source type";
        return 0;
    }

    std::string name() override {
        return "#" + std::to_string(info_.index);
    }

    const NuvotonSensorSourceInfo* GetSource() override {
        uint8_t selected;
        if (!chip_->ReadByte(info_.select, &selected).ok()) {
            return nullptr;
        }
        const auto it = table_.find(selected);
        if (it == table_.end()) {
            return nullptr;
        }
        return &it->second;
    }

    Status SetSource(const std::string& target) override {
        for (const auto& [index, source] : table_) {
            if (source.name == target) {
                return chip_->WriteByte(info_.select, index);
            }
        }
        return Status(ENOENT, "unkonwn source");
    }

    void DumpInfo(std::ostream& out) override {
        out << "Multi sensor " << name() << std::endl;
        const NuvotonSensorSourceInfo* source = GetSource();
        if (source == nullptr) {
            out << "Unknown source set" << std::endl;
            return;
        }
        switch (source->type) {
            case NuvotonSensorType::kTemp:
                out << "  Temp " << source->name << " at " << value() << std::endl;
                break;
            case NuvotonSensorType::kVolt:
                out << "  Voltage " << source->name << " at " << value() << std::endl;
                break;
        }
    }

  private:
    const NuvotonMultiSensorInfo info_;
    const NuvotonSensorSourceTable table_;
    NuvotonChip* chip_;
};

std::unique_ptr<NuvotonMultiSensor> CreateNuvotonMultiSensor(
    const NuvotonMultiSensorInfo& info, const NuvotonSensorSourceTable& table,
    NuvotonChip* chip) {
    return std::make_unique<NuvotonMultiSensorImpl>(info, table, chip);
}

}
