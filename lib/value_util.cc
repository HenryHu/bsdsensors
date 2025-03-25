/*
 * value_util.cc
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "value_util.h"
#include "nuvoton_fan_control.h"

namespace bsdsensors {

using namespace std;

void PrintTempValue(const TemperatureProto& temp, std::ostream& out) {
    out << "Temperature " << temp.name() << ": " << temp.value() << " C";
    if (!temp.source().empty()) {
        out << " from " << temp.source();
    }
    out << std::endl;
}

void PrintFanSpeedValue(const FanProto& fan, std::ostream& out) {
    out << "  Speed: " << fan.speed().value() << " RPM" << std::endl;
}

void PrintFanStatus(const FanProto& fan, std::ostream& out) {
    out << "Fan " << fan.name() << std::endl;
    if (fan.has_speed()) {
        PrintFanSpeedValue(fan, out);
    }
    if (fan.has_control()) {
        out << fan.control();
    }
}

void PrintVoltValue(const VoltageProto& volt, std::ostream& out) {
    out << "Voltage " << volt.name() << ": " << volt.value() << " V";
    out << std::endl;
}

void PrintSensorValues(const SensorsProto& sensors, std::ostream& out) {
    for (const auto& temp : sensors.temperatures()) {
        PrintTempValue(temp, out);
    }
    for (const auto& volt : sensors.voltages()) {
        PrintVoltValue(volt, out);
    }
    for (const auto& fan : sensors.fans()) {
        PrintFanStatus(fan, out);
    }
}

std::ostream& operator<<(std::ostream& out,
                         const FanControlProto& fan_control) {
    if (fan_control.has_current_percent()) {
        out << "  Current: " << (int)(fan_control.current_percent() * 100) << "%" << std::endl;
    }
    if (fan_control.has_current_method()) {
        out << "  Control method: " << fan_control.current_method() << std::endl;
    }
    if (!fan_control.temp_source().empty()) {
        out << "  Temp source: " << fan_control.temp_source();
        if (fan_control.has_temp_value()) {
            out << " at " << fan_control.temp_value() << " C";
        }
        out << std::endl;
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
    return out;
}

void PrintSelectedSensors(const SensorsProto& sensors, const string& selected,
                          bool value_only, std::ostream& out) {
    for (const auto& sensor : StrSplit(selected, ',')) {
        const auto& parts = StrSplit(sensor, ':');
        if (parts.size() != 2) {
            LOG(ERROR) << "malformed sensor: " << sensor;
            continue;
        }

        bool found = false;
        if (parts[0] == "fan") {
            for (const auto& fan : sensors.fans()) {
                if (fan.name() == parts[1]) {
                    out << fan.speed().value() << endl;
                    found = true;
                }
            }
        } else if (parts[0] == "temp") {
            for (const auto& temp : sensors.temperatures()) {
                if (temp.name() == parts[1]) {
                    out << temp.value() << endl;
                    found = true;
                }
            }
        } else if (parts[0] == "volt") {
            for (const auto& volt : sensors.voltages()) {
                if (volt.name() == parts[1]) {
                    out << volt.value() << endl;
                    found = true;
                }
            }
        } else {
            LOG(ERROR) << "unknown sensor type: " << parts[0];
            continue;
        }
        if (!found) {
            LOG(ERROR) << "sensor not found: " << parts[1];
        }
    }
}

}  // namespace bsdsensors
