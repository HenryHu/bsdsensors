/*
 * util.cc
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "util.h"

#include <iostream>

namespace bsdsensors {

// Return @bits in @byte.
uint8_t BitsFromByte(const Bits& bits, uint8_t byte) {
    assert(bits.first <= 8);
    assert(bits.last >= 0);
    assert(bits.first >= bits.last);

    if (bits.first - bits.last + 1 == 8) {
        return byte;
    }

    uint8_t my_part = (byte >> bits.last) & ((1 << bits.width()) - 1);

    if (bits.next) {
        return (my_part << bits.other_parts_len) |
               BitsFromByte(*bits.next, byte);
    } else {
        return my_part;
    }
}

// Return @byte with @bits replaced by @value.
uint8_t BitsToByte(const Bits& bits, uint8_t byte, uint8_t value) {
    assert(bits.first <= 8);
    assert(bits.last >= 0);
    assert(bits.first >= bits.last);

    if (bits.first - bits.last + 1 == 8) {
        return value;
    }

    uint8_t mask = (1 << bits.width()) - 1;
    uint8_t my_ret = (byte & ~(mask << bits.last)) |
                     (((value >> bits.other_parts_len) & mask) << bits.last);
    if (bits.next) {
        return BitsToByte(*bits.next, my_ret,
                          value & ((1 << bits.other_parts_len) - 1));
    } else {
        return my_ret;
    }
}

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

void PrintFanSpeedValue(const FanSpeedProto& fan_speed, bool value_only,
                        std::ostream& out) {
    if (value_only) {
        out << fan_speed.value();
    } else {
        out << "Fan " << fan_speed.name() << ": " << fan_speed.value()
            << " RPM";
    }
    out << std::endl;
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
    for (const auto& fan_speed : sensors.fan_speeds()) {
        PrintFanSpeedValue(fan_speed, false, out);
    }
}

std::vector<std::string> StrSplit(const std::string& str, const char delim) {
    std::vector<std::string> result;
    int start = 0;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == delim) {
            if (start < i) {
                result.push_back(str.substr(start, i - start));
            }
            start = i + 1;
        }
    }
    if (start < str.length()) {
        result.push_back(str.substr(start));
    }
    return result;
}

}  // namespace bsdsensors
