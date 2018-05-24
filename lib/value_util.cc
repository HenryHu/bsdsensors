/*
 * value_util.cc
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "value_util.h"
#include "nuvoton_fan_control.h"

namespace bsdsensors {

void PrintTempValue(const TemperatureProto& temp, bool value_only,
                    std::ostream& out) {
    if (value_only) {
        out << temp.value();
    } else {
        out << "Temperature " << temp.name() << ": " << temp.value() << " C";
        if (!temp.source().empty()) {
            out << " from " << temp.source();
        }
    }
    out << std::endl;
}

void PrintFanSpeedValue(const FanProto& fan, bool value_only,
                        std::ostream& out) {
    if (value_only) {
        out << fan.speed().value();
    } else {
        out << "Fan " << fan.name() << ": " << fan.speed().value() << " RPM";
    }
    out << std::endl;
}

void PrintFanStatus(const FanProto& fan, std::ostream& out) {
    PrintFanSpeedValue(fan, false, out);
    PrintFanControlStatus(fan.control(), out);
}

void PrintVoltValue(const VoltageProto& volt, bool value_only,
                    std::ostream& out) {
    if (value_only) {
        out << volt.value();
    } else {
        out << "Voltage " << volt.name() << ": " << volt.value() << " V";
    }
    out << std::endl;
}

void PrintSensorValues(const SensorsProto& sensors, std::ostream& out) {
    for (const auto& temp : sensors.temperatures()) {
        PrintTempValue(temp, false, out);
    }
    for (const auto& volt : sensors.voltages()) {
        PrintVoltValue(volt, false, out);
    }
    for (const auto& fan : sensors.fans()) {
        PrintFanStatus(fan, out);
    }
}

void PrintFanControlStatus(const FanControlProto& fan_control,
                           std::ostream& out) {
    out << "  Current: " << (int)(fan_control.current_percent() * 100) << "%";
    out << " Control method: " << fan_control.current_method() << std::endl;
    if (!fan_control.temp_source().empty()) {
        out << "  Temp source: " << fan_control.temp_source() << " at "
            << fan_control.temp_value() << " C" << std::endl;
    }
    for (const auto& method : fan_control.methods()) {
        out << "  Method " << method.name() << ":" << std::endl;
        switch (method.method_case()) {
            case FanControlMethodProto::kGenericMethod: {
                break;
            }
            case FanControlMethodProto::kNuvotonMethod: {
                out << method.nuvoton_method();
                break;
            }
            case FanControlMethodProto::METHOD_NOT_SET: {
                break;
            }
        }
    }
}

}  // namespace bsdsensors
