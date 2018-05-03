/*
 * port_io.cc
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "port_io.h"

#include <sys/cdefs.h>
#include <sys/types.h>
#include <machine/cpufunc.h>
#include <sys/ioctl.h>
#include <dev/io/iodev.h>
#include <machine/iodev.h>
#include <memory>
#include <fcntl.h>
#include <unistd.h>

const char* kIODevice = "/dev/io";

class PortIOImpl : public PortIO {
   public:
    PortIOImpl() : io_fd_(-1) {}
    ~PortIOImpl() override {
        if (io_fd_ >= 0) close(io_fd_);
    }

    Status Init() override {
        io_fd_ = open(kIODevice, O_RDWR);
        if (io_fd_ < 0) {
            return Errno();
        }
        return OkStatus();
    }

    Status ReadByte(const AddressType& address, uint8_t* data) override {
        struct iodev_pio_req req;
        req.access = IODEV_PIO_READ;
        req.port = address;
        req.width = 1;

        if (ioctl(io_fd_, IODEV_PIO, &req) < 0) {
            return Errno();
        }

        *data = req.val;
        return OkStatus();
    }
    Status WriteByte(const AddressType& address, const uint8_t data) override {
        struct iodev_pio_req req;
        req.access = IODEV_PIO_WRITE;
        req.port = address;
        req.width = 1;
        req.val = data;

        if (ioctl(io_fd_, IODEV_PIO, &req) < 0) {
            return Errno();
        }

        return OkStatus();
    }

   private:
    int io_fd_;
};

std::unique_ptr<PortIO> CreatePortIO() {
    return std::make_unique<PortIOImpl>();
}
