/*
 * fake_port_io.h
 * Copyright (C) 2025 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#ifndef __BSDSENSORS_TEST_FAKE_PORT_IO_H_
#define __BSDSENSORS_TEST_FAKE_PORT_IO_H_

#include "port_io.h"

#include <map>

namespace bsdsensors {

class FakePortIO : public PortIO {
  public:
    virtual ~FakePortIO() {}

    Status Init() override { return OkStatus(); }
    Status ReadByte(const AddressType& address, uint8_t* data) override { return OkStatus(); }
    Status WriteByte(const AddressType& address,
            const uint8_t data) override { return OkStatus(); }
};

std::unique_ptr<FakePortIO> CreateFakePortIO(
        std::map<uint8_t, uint8_t> registers);

}

#endif // __BSDSENSORS_TEST_FAKE_PORT_IO_H_
