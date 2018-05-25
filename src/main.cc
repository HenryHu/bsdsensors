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
#include "dev_db.h"
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
DEFINE_string(request, "", "request configuration change");
DEFINE_string(chip, "", "specify which chip to print");

using namespace std;
using namespace bsdsensors;

const std::function<std::unique_ptr<Chip>()> kCreateChips[] = {
    CreateNuvotonChip, CreateITEChip, CreateFintekChip, CreateMicrochipChip};

const char* kUsageMessage = "bsdsensors - Tool to get hardware sensor values";

int main(int argc, char** argv) {
    gflags::SetUsageMessage(kUsageMessage);
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    google::InitGoogleLogging(argv[0]);

    if (FLAGS_debug) {
        FLAGS_logtostderr = true;
    }

    std::unique_ptr<DeviceDb> dev_db = CreateDeviceDb();

    for (const auto& CreateChip : kCreateChips) {
        auto chip = CreateChip();
        if (chip->Detect()) {
            chip->set_name(dev_db->Register(chip->name(), nullptr));

            if (!FLAGS_chip.empty() && FLAGS_chip != chip->name()) {
                continue;
            }

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
                PrintSelectedSensors(sensors, FLAGS_sensors, FLAGS_value, cout);
            }
        }
    }
}
