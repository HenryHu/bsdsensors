/*
 * nuvoton_chip_info.h
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#ifndef __BSDSENSORS_NUVOTON_CHIP_INFO_H__
#define __BSDSENSORS_NUVOTON_CHIP_INFO_H__

#include <map>
#include <cstdint>
#include <string>
#include <vector>
#include <optional>

#include "chip_info.h"
#include "nuvoton_chip.h"

namespace bsdsensors {

// Most boards can measure 0~2V, so unit = 2V / 255 = ~8mV.
// Some boards can measure 0~4V, so unit would be 16mV instead.
constexpr double kDefaultVoltUnit = 0.008;  // 1 = 8mV

enum class NuvotonTempSource {
    kSourceUnknown = 0,
    kSourceSYSTIN = 1,
    kSourceCPUTIN = 2,
    kSourceAUXTIN0 = 3,
    kSourceAUXTIN1 = 4,
    kSourceAUXTIN2 = 5,
    kSourceAUXTIN3 = 6,
    kSourceReserved = 7,
    kSourceSMBUSMASTER0 = 8,
    kSourceSMBUSMASTER1 = 9,
    kSourceSMBUSMASTER2 = 10,
    kSourceSMBUSMASTER3 = 11,
    kSourceSMBUSMASTER4 = 12,
    kSourceSMBUSMASTER5 = 13,
    kSourceSMBUSMASTER6 = 14,
    kSourceSMBUSMASTER7 = 15,
    kSourcePECI0 = 16,
    kSourcePECI1 = 17,
    kSourcePCHCPUMAX = 18,
    kSourcePCH = 19,
    kSourcePCHCPU = 20,
    kSourcePCHMCH = 21,
    kSourceDIM0 = 22,
    kSourceDIM1 = 23,
    kSourceDIM2 = 24,
    kSourceDIM3 = 25,
    kSourceBYTE = 26,
    kSource27 = 27,
    kSource28 = 28,
    kSource29 = 29,
    kSource30 = 30,
    kSource31 = 31,
    kSourceVirtualTemp1 = 32,
    kSourceVirtualTemp2 = 33,
    kSourceVirtualTemp3 = 34,
    kSourcePECI0Calib = 35,
    kSourcePECI1Calib = 36,
    kSourceAUXTIN4 = 37,
    kSourceBYTE0 = 38,
    kSourceBYTE1 = 39,
    kSourcePECI2 = 40,
    kSourcePECI3 = 41,
};

constexpr int kMaxSource = 37;

using NuvotonTempSourceTable = std::map<NuvotonTempSource, uint8_t>;

extern std::string GetNuvotonSourceName(NuvotonTempSource source);
extern Status GetNuvotonSourceByName(const std::string& name,
                                     NuvotonTempSource* source);

constexpr int kFastAccessBank = -1;

enum NuvotonTempSensorType {
    kThermistorSensor = 0,
    kDiodeSensor = 1,
};

struct NuvotonThermalCruiseInfo {
    // Target temperature.
    NuvotonChip::AddressType target_temp;
    NuvotonChip::AddressType tolerance;
    NuvotonChip::AddressType start_value;
    NuvotonChip::AddressType stop_value;
    NuvotonChip::AddressType keep_min_output;
    NuvotonChip::AddressType stop_time;
    NuvotonChip::AddressType step_up_time;
    NuvotonChip::AddressType step_down_time;
    // If temperature reaches this, fan will run at 100%.
    NuvotonChip::AddressType critical_temp;
};

struct NuvotonSpeedCruiseInfo {
    // Target fan speed.
    NuvotonChip::AddressType target_speed_count_low;
    NuvotonChip::AddressType target_speed_count_high;
    NuvotonChip::AddressType tolerance_low;
    NuvotonChip::AddressType tolerance_high;
    NuvotonChip::AddressType step_up_time;
    NuvotonChip::AddressType step_down_time;
    NuvotonChip::AddressType step_up_value;
    NuvotonChip::AddressType step_down_value;
    NuvotonChip::AddressType keep_min_output;
};

struct NuvotonSmartFanInfo {
    bool available;
    NuvotonThermalCruiseInfo thermal_cruise;
    NuvotonSpeedCruiseInfo speed_cruise;
};

struct NuvotonSmartFan4ControlPointInfo {
    NuvotonChip::AddressType temp;
    NuvotonChip::AddressType power;
};

struct NuvotonSmartFan4Info {
    bool available;
    std::vector<NuvotonSmartFan4ControlPointInfo> control_points;
};

enum class NuvotonFanControlMode {
    kManualMode = 0,
    kThermalCruise = 1,
    kSpeedCruise = 2,
    kSmartFan3 = 3,
    kSmartFan4 = 4,
};

struct NuvotonFanControlInfo {
    // Selects control mode.
    NuvotonChip::AddressType mode_select;
    // FAN output for PWM, duty cycle = value / 255
    NuvotonChip::AddressType output_value_write;
    // FAN output for DC, output volt = AVcc * value / 64
    NuvotonChip::AddressType output_value_write_dc;
    // Whether DC output is supported for this FAN.
    bool support_dc = false;
    // If support_dc = false, then output_type is invalid
    // selects DC output (1) or PWM output (0).
    NuvotonChip::AddressType output_type;
    // Reads the current FAN output value. No separate register for old chips.
    NuvotonChip::AddressType output_value_read;

    // Allows the temp source to be selected.
    NuvotonChip::AddressType temp_source;
    // Selected temp source's temp value, not supported on older chips.
    NuvotonChip::AddressType temp_value_int, temp_value_frac;

    // Fan control methods.
    NuvotonSmartFanInfo smart_fan;
    NuvotonSmartFan4Info smart_fan4;

    // Fixed temp source.
    NuvotonTempSource fixed_temp_source;
    // Overrides the global temp source table.
    std::map<uint8_t, NuvotonTempSource> source_select;
};

struct NuvotonFanInfo {
    std::string name;
    // RPM, only available on some chips.
    NuvotonChip::AddressType rpm_high, rpm_low;
    // RPM by cycle count. RPM = 1.35e6 / count / 2^divisor.
    NuvotonChip::AddressType count, divisor;
    std::optional<NuvotonFanControlInfo> control;
};

struct NuvotonTempInfo {
    std::string name;
    // Temperature, integer part.
    NuvotonChip::AddressType val_int;
    // Temperature, fraction part.
    // Often there's only 1 bit, which means 0.5C.
    NuvotonChip::AddressType val_frac;
    bool has_peci_frac;
    // Whether the temperature source can be changed.
    bool can_select;
    // Select a specific source, only works if can_select is true.
    NuvotonChip::AddressType select;
    // This value is added to the monitoring value.
    NuvotonChip::AddressType offset;
    // Sensor type: 1 for diode, 0 for thermistor.
    // see NuvotonTempSensorType
    NuvotonChip::AddressType sensor_type;
};

struct NuvotonVoltInfo {
    std::string name;
    // Voltage value. Typically voltage = 8mV * value; some older chips use 16mV.
    NuvotonChip::AddressType addr;
    // Result = raw value * alpha + beta
    // Since the chip can only measure 0~2V, 3.3V needs to be scaled down with
    // external resistors, and to get the real voltage, it needs to be scaled
    // back up. As a result, we often set alpha = 2.0 for 3.3V.
    double alpha = 1.0, beta = 0.0;
    NuvotonChip::AddressType enable;
};

struct NuvotonChipInfo {
    std::map<uint16_t, std::string> device_id_to_name;
    NuvotonChip::AddressType vendor_id_addr;
    std::vector<NuvotonFanInfo> fans;
    NuvotonTempSourceTable temp_table;
    std::vector<NuvotonTempInfo> temps;
    std::vector<NuvotonVoltInfo> volts;
    std::string notes;
    NuvotonChip::AddressType bank_select;
    double volt_unit = kDefaultVoltUnit;
};

}  // namespace bsdsensors

#endif  // __BSDSENSORS_NUVOTON_CHIP_INFO_H__
