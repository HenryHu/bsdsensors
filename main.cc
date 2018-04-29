/*
 * main.cc
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "super_io.h"
#include <iostream>
#include <unistd.h>

using namespace std;

int main() {
    auto io = CreateSuperIO(0x2E);
    CHECK(io->Init(), "Fail to init Port IO");

    uint8_t result;

    {
        SuperIOLock lock(io.get());
        uint16_t id = 0;
        CHECK(io->ReadByte(0x20, &result), "Fail to read ID");
        id |= (uint16_t)result << 8;
        CHECK(io->ReadByte(0x21, &result), "Fail to read ID");
        id |= result;
        cout << "Found SuperIO ID: " << hex << "0x" << id << endl;
    }
}
