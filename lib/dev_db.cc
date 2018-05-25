/*
 * dev_db.cc
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "dev_db.h"
#include <sstream>
#include <map>

class DeviceDbImpl : public DeviceDb {
   public:
    std::string Register(const std::string& name, int* assigned_no) override {
        int num = count_[name]++;
        if (assigned_no) *assigned_no = num;

        std::ostringstream oss;
        oss << name << "-" << num;
        return oss.str();
    }

   private:
    std::map<std::string, int> count_;
};

std::unique_ptr<DeviceDb> CreateDeviceDb() {
    return std::make_unique<DeviceDbImpl>();
}
