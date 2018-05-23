/*
 * main.cc
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "nuvoton_chip.h"
#include "ite_chip.h"
#include "fintek_chip.h"
#include "microchip_chip.h"
#include "util.h"
#include <iostream>
#include <unistd.h>
#include <gflags/gflags.h>
#include <glog/logging.h>

DEFINE_string(sensors, "", "comma-separated list of sensors to print");
DEFINE_bool(debug, false, "print debug output");
DEFINE_bool(value, false, "print value only");

using namespace std;
using namespace bsdsensors;

const std::function<std::unique_ptr<Chip>()> kCreateChips[] = {
    CreateNuvotonChip, CreateITEChip, CreateFintekChip, CreateMicrochipChip};

const char* kUsageMessage = "bsdsensors - Tool to get hardware sensor values";

void PrintSelectedSensors(const SensorsProto& sensors, const string& selected) {
    for (const auto& sensor : StrSplit(selected, ',')) {
        const auto& parts = StrSplit(sensor, ':');
        if (parts.size() != 2) {
            LOG(ERROR) << "malformed sensor: " << sensor;
            continue;
        }

        bool found = false;
        if (parts[0] == "fan") {
            for (const auto& fan_speed : sensors.fan_speeds()) {
                if (fan_speed.name() == parts[1]) {
                    PrintFanSpeedValue(fan_speed, FLAGS_value, cout);
                    found = true;
                }
            }
        } else if (parts[0] == "temp") {
            for (const auto& temp : sensors.temperatures()) {
                if (temp.name() == parts[1]) {
                    PrintTempValue(temp, FLAGS_value, cout);
                    found = true;
                }
            }
        } else if (parts[0] == "volt") {
            for (const auto& volt : sensors.voltages()) {
                if (volt.name() == parts[1]) {
                    PrintVoltValue(volt, FLAGS_value, cout);
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

int main(int argc, char** argv) {
    gflags::SetUsageMessage(kUsageMessage);
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    google::InitGoogleLogging(argv[0]);

    if (FLAGS_debug) {
        FLAGS_logtostderr = true;
    }

    for (const auto& CreateChip : kCreateChips) {
        auto chip = CreateChip();
        if (chip->Detect()) {
            if (FLAGS_debug) {
                chip->DumpInfo(cerr);
            }
            SensorsProto sensors;
            Status status = chip->GetSensorValues(&sensors);
            if (!status.ok()) {
                LOG(ERROR) << "Error reading sensors: "
                           << status.error_message();
                continue;
            }
            if (FLAGS_sensors.empty()) {
                PrintSensorValues(sensors, cout);
            } else {
                PrintSelectedSensors(sensors, FLAGS_sensors);
            }
        }
    }
}
