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
#include "value_util.h"
#include <iostream>
#include <unistd.h>
#include <gflags/gflags.h>
#include <glog/logging.h>
#include <google/protobuf/util/json_util.h>

DEFINE_string(sensors, "", "comma-separated list of sensors to print");
DEFINE_bool(debug, false, "print debug output");
DEFINE_bool(value, false, "print value only");
DEFINE_bool(proto, false, "print raw proto");
DEFINE_bool(json, false, "print proto in json");

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
            for (const auto& fan : sensors.fans()) {
                if (fan.name() == parts[1]) {
                    PrintFanSpeedValue(fan, FLAGS_value, cout);
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
                if (FLAGS_proto) {
                    cout << sensors.DebugString() << endl;
                } else if (FLAGS_json) {
                    string json_string;

                    google::protobuf::util::JsonPrintOptions options;
                    options.add_whitespace = true;
                    options.always_print_primitive_fields = true;
                    options.preserve_proto_field_names = true;

                    MessageToJsonString(sensors, &json_string, options);
                    cout << json_string << endl;
                } else {
                    PrintSensorValues(sensors, cout);
                }
            } else {
                PrintSelectedSensors(sensors, FLAGS_sensors);
            }
        }
    }
}
