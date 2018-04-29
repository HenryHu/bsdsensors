/*
 * nuvoton_chip.cc
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "nuvoton_chip.h"
#include "super_io.h"

#include <iostream>
using namespace std;

const uint32_t kNuvotonPorts[] = {0x2E, 0x4E};

class NuvotonChipImpl : public NuvotonChip {
   public:
    NuvotonChipImpl() {}
    ~NuvotonChipImpl() override {}
    bool Detect() override {
        for (const auto& port : kNuvotonPorts) {
            io_ = CreateSuperIO(port);
            if (!io_->Init().ok()) {
                return false;
            }

            {
                SuperIOLock lock(io_.get());
                uint16_t id = 0;
                uint8_t result;
                if (!io_->ReadByte(0x20, &result).ok()) {
                    continue;
                }
                id |= (uint16_t)result << 8;
                if (!io_->ReadByte(0x21, &result).ok()) {
                    continue;
                }
                id |= result;
                if (id != 0xffff) {
                    cout << "Found SuperIO ID: " << hex << "0x" << id
                         << " at 0x" << port << endl;
                    return true;
                }
            }
            io_.reset();
        }
        return false;
    }

   private:
    std::unique_ptr<SuperIO> io_;
};

std::unique_ptr<NuvotonChip> CreateNuvotonChip() {
    return std::make_unique<NuvotonChipImpl>();
}
