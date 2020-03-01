/*
 * dev_db.h
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#ifndef __BSDSENSORS_DEV_DB_H__
#define __BSDSENSORS_DEV_DB_H__

#include <string>
#include <memory>

class DeviceDb {
   public:
    virtual std::string Register(const std::string& name, int* assigned_no) = 0;

    virtual ~DeviceDb() {}
};

std::unique_ptr<DeviceDb> CreateDeviceDb();

#endif  // __BSDSENSORS_DEV_DB_H__
