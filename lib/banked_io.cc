/*
 * banked_io.cc
 * Copyright (C) 2025 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "banked_io.h"

#include "port_io.h"

#include <glog/logging.h>

namespace bsdsensors {

class BasicBankedIO : public BankedIO {
  public:
    BasicBankedIO(const PortAddress addr_port, const PortAddress data_port,
            const BankedAddress& bank_select, PortIO* port_io)
        : addr_port_(addr_port), data_port_(data_port),
          bank_select_(bank_select), port_io_(port_io) {}
    virtual ~BasicBankedIO() {}

    Status Init() override { return OkStatus(); }
    Status ReadByte(const AddressType& addr, uint8_t* data) override {
        RETURN_IF_ERROR(SelectBank(addr.bank));
        RETURN_IF_ERROR(port_io_->WriteByte(addr_port_, addr.addr));
        uint8_t value;
        RETURN_IF_ERROR(port_io_->ReadByte(data_port_, &value));
        uint8_t my_part = BitsFromByte(addr.bits, value);
        if (addr.next) {
            uint8_t other_part;
            RETURN_IF_ERROR(ReadByte(*addr.next.get(), &other_part));
            *data = (my_part << addr.other_parts_len) | other_part;
        } else {
            *data = my_part;
        }
        VLOG(1) << "read from " << addr << " result " << (int)*data;
        return OkStatus();
    }
    Status WriteByte(const AddressType& addr, const uint8_t data) override {
        uint8_t orig = 0;
        if (!addr.bits.full()) {
            RETURN_IF_ERROR(ReadByte(addr, &orig));
        }
        RETURN_IF_ERROR(SelectBank(addr.bank));
        RETURN_IF_ERROR(port_io_->WriteByte(addr_port_, addr.addr));
        uint8_t my_part = data >> addr.other_parts_len;
        RETURN_IF_ERROR(port_io_->WriteByte(
            data_port_, BitsToByte(addr.bits, orig, my_part)));
        if (addr.next) {
            uint8_t other_part = data & ((1 << addr.other_parts_len) - 1);
            return WriteByte(*addr.next.get(), other_part);
        } else {
            return OkStatus();
        }

    }

    Status ReadWord(const AddressType& addr, uint16_t* data) override {
        RETURN_IF_ERROR(SelectBank(addr.bank));
        RETURN_IF_ERROR(port_io_->WriteByte(addr_port_, addr.addr));
        uint8_t value;
        RETURN_IF_ERROR(port_io_->ReadByte(data_port_, &value));
        // Extend to 16 bits
        uint16_t my_part = BitsFromByte(addr.bits, value);
        if (addr.next) {
            uint8_t other_part;
            RETURN_IF_ERROR(ReadByte(*addr.next.get(), &other_part));
            *data = (my_part << addr.other_parts_len) | other_part;
        } else {
            *data = my_part;
        }
        VLOG(1) << "read from " << addr << " result " << (int)*data;
        return OkStatus();
    }

  private:
    Status SelectBank(const uint8_t bank_no) {
        uint8_t orig = 0;
        if (!bank_select_.bits.full()) {
            RETURN_IF_ERROR(ReadByte(bank_select_, &orig));
        }
        RETURN_IF_ERROR(port_io_->WriteByte(addr_port_, bank_select_.addr));
        uint8_t my_part = bank_no >> bank_select_.other_parts_len;
        return port_io_->WriteByte(
                data_port_, BitsToByte(bank_select_.bits, orig, my_part));
    }

    const PortAddress addr_port_, data_port_;
    const BankedAddress bank_select_;

    PortIO* port_io_;
};


class ECSpaceBankedIO : public BankedIO {
  public:

    Status Init() override { return OkStatus(); }
    Status ReadByte(const AddressType& address, uint8_t* data) override {
        return OkStatus();
    }
    virtual Status ReadWord(const AddressType& addr, uint16_t* data) override {
        return OkStatus();
    }
    Status WriteByte(const AddressType& address, const uint8_t data) override {
        return OkStatus();
    }
};

std::unique_ptr<BankedIO> CreateBasicBankedIO(
    const PortAddress addr_port, const PortAddress data_port,
    const BankedAddress& bank_select, PortIO* port_io) {
    return std::make_unique<BasicBankedIO>(addr_port, data_port, bank_select,
            port_io);
}

std::unique_ptr<BankedIO> CreateECSpacecBankedIO() {
    return std::make_unique<ECSpaceBankedIO>();
}

}
