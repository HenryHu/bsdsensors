/*
 * status.h
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#ifndef __BSDSENSORS_STATUS_H__
#define __BSDSENSORS_STATUS_H__

#include <string>

class Status {
   public:
    Status(int code, const std::string& error_message);

    int error_code() const;
    bool ok() const;
    std::string error_message() const;

   private:
    int error_code_;
    std::string error_message_;
};

Status OkStatus();

// Return a Status with current errno.
Status Errno();

void CHECK(const Status& status, const std::string& message);

#define RETURN_IF_ERROR(result) \
    do {                        \
        Status status = result; \
        if (!status.ok()) {     \
            return status;      \
        }                       \
    } while (0)

#endif  // __BSDSENSORS_STATUS_H__
