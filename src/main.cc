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
#include <iostream>
#include <unistd.h>

using namespace std;
using namespace bsdsensors;

const std::function<std::unique_ptr<Chip>()> kCreateChips[] = {
    CreateNuvotonChip, CreateITEChip, CreateFintekChip, CreateMicrochipChip};

int main() {
    for (const auto& CreateChip : kCreateChips) {
        auto chip = CreateChip();
        if (chip->Detect()) {
            chip->DumpInfo(cout);

            SensorsProto sensors;
            Status status = chip->GetSensorValues(&sensors);
            if (!status.ok()) {
                cerr << "Error reading sensors: " << status.error_message()
                     << endl;
                continue;
            }

            cout << sensors.DebugString() << endl;
        }
    }
}
