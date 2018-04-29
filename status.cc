/*
 * status.cc
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "status.h"

#include <errno.h>

#include <iostream>

using std::string;

const int E_OK = 0;
const int kErrorMsgLen = 100;

Status::Status(int code, const string& error_message)
    : error_code_(code), error_message_(error_message) {}

int Status::error_code() const { return error_code_; }

bool Status::ok() const { return error_code_ == E_OK; }

string Status::error_message() const { return error_message_; }

Status OkStatus() { return Status(E_OK, ""); }

Status Errno() {
    int err = errno;
    char error_buf[kErrorMsgLen];
    strerror_r(err, error_buf, sizeof(error_buf));
    return Status(err, error_buf);
}

void CHECK(const Status& status, const std::string& message) {
    if (!status.ok()) {
        const string& error_msg = message + ": " + status.error_message();
        std::cerr << error_msg << std::endl;
        throw std::runtime_error(error_msg);
    }
}
