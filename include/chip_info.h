/*
 * chip_info.h
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#ifndef __BSDSENSORS_CHIP_INFO_H__
#define __BSDSENSORS_CHIP_INFO_H__

#include <map>

namespace bsdsensors {

template <typename ChipInfo>
class KnownChips {
   public:
    void RegisterChipInfo(const ChipInfo& info) {
        chips_.insert(std::make_pair(info.device_id, info));
    }

    ChipInfo* Find(uint16_t device_id) {
        auto ret = chips_.find(device_id);
        if (ret != chips_.end()) {
            return &ret->second;
        } else {
            return nullptr;
        }
    }

   private:
    std::map<uint16_t, ChipInfo> chips_;
};

template <typename ChipInfo>
class RegisterChip {
   public:
    RegisterChip(const ChipInfo& info, KnownChips<ChipInfo>* chips) {
        chips->RegisterChipInfo(info);
    }
};

}  // namespace bsdsensors

#endif  // __BSDSENSORS_CHIP_INFO_H__
