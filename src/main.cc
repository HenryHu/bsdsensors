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
#include "request.pb.h"
#include <iostream>
#include <unistd.h>
#include <gflags/gflags.h>
#include <glog/logging.h>
#include <google/protobuf/util/json_util.h>
#include <google/protobuf/text_format.h>

DEFINE_string(sensors, "", "comma-separated list of sensors to print");
DEFINE_bool(debug, false, "print debug output");
DEFINE_bool(quiet, false, "be quiet, less log");
DEFINE_bool(value, false, "print value only");
DEFINE_bool(proto, false, "print raw proto");
DEFINE_bool(json, false, "print proto in json");
DEFINE_string(request, "", "request configuration change");
DEFINE_string(chip, "", "specify which chip to print");
DEFINE_bool(dump, false, "dump everything (can be dangerous)");

using namespace std;
using namespace bsdsensors;

using google::protobuf::TextFormat;
using google::protobuf::util::JsonParseOptions;
using google::protobuf::util::JsonPrintOptions;

const std::function<std::unique_ptr<Chip>(std::unique_ptr<PortIO>)> kCreateChips[] = {
    CreateNuvotonChip, CreateITEChip, CreateFintekChip, CreateMicrochipChip};

const char* kUsageMessage = "Tool to get hardware sensor values";

void PrintAllSensors(const SensorsProto& sensors, bool in_proto, bool in_json) {
    if (in_proto) {
        cout << sensors.DebugString() << endl;
    } else if (in_json) {
        string json_string;

        google::protobuf::util::JsonPrintOptions options;
        options.add_whitespace = true;
        options.preserve_proto_field_names = true;

        ABSL_QCHECK_OK(MessageToJsonString(sensors, &json_string, options));
        cout << json_string << endl;
    } else {
        PrintSensorValues(sensors, cout);
    }
}

int main(int argc, char** argv) {
    gflags::SetUsageMessage(kUsageMessage);
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    google::InitGoogleLogging(argv[0]);
    if (FLAGS_debug) {
        FLAGS_minloglevel = 0; // INFO
    } else {
        FLAGS_minloglevel = 1; // WARNING
    }

    if (!FLAGS_quiet) {
        FLAGS_logtostderr = true;
    }

    std::unique_ptr<DeviceDb> dev_db = CreateDeviceDb();

    bool detected = false;
    for (const auto& CreateChip : kCreateChips) {
        auto chip = CreateChip(CreatePortIO());
        if (!chip->Detect()) continue;
        detected = true;
        chip->set_name(dev_db->Register(chip->name(), nullptr));

        if (!FLAGS_chip.empty() && FLAGS_chip != chip->name()) {
            continue;
        }

        if (FLAGS_debug) {
            chip->DumpInfo(cerr);
        }

        if (FLAGS_dump) {
            if (FLAGS_proto) {
                TestData proto = chip->DumpProto();
                std::string out;
                google::protobuf::TextFormat::PrintToString(proto, &out);
                std::cout << out << std::endl;
            } else {
                chip->DumpAll(cerr);
            }
            break;
        }

        if (!FLAGS_request.empty()) {
            Request request;
            if (!JsonStringToMessage(FLAGS_request, &request,
                        JsonParseOptions())
                    .ok() &&
                    !TextFormat::ParseFromString(FLAGS_request, &request)) {
                LOG(ERROR) << "Malformed request " << FLAGS_request;
                continue;
            }

            Status status = chip->ProcessRequest(request);
            if (!status.ok()) {
                LOG(ERROR) << "Process error: " << status.error_message();
            } else {
                LOG(INFO) << "Request processed";
            }
        } else {
            SensorsProto sensors;
            Status status = chip->GetSensorValues(&sensors);
            if (!status.ok()) {
                LOG(ERROR)
                    << "Error reading sensors: " << status.error_message();
                continue;
            }
            if (FLAGS_sensors.empty()) {
                PrintAllSensors(sensors, FLAGS_proto, FLAGS_json);
            } else {
                PrintSelectedSensors(sensors, FLAGS_sensors, FLAGS_value,
                        cout);
            }
        }
        break;
    }

    if (!detected) {
        LOG(ERROR) << "No chip detected. Make sure you're running with root privilege.";
        LOG(ERROR) << "You can also try to run with --debug.";
    }
}
