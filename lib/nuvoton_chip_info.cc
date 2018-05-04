/*
 * nuvoton_chip_info.cc
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "nuvoton_chip_info.h"

std::map<uint16_t, NuvotonChipInfo>* KnownNuvotonChips() {
    static std::map<uint16_t, NuvotonChipInfo> known_chips;
    return &known_chips;
}

void RegisterNuvotonChipInfo(const NuvotonChipInfo& info) {
    KnownNuvotonChips()->insert(std::make_pair(info.device_id, info));
}

NuvotonChipInfo* FindNuvotonChip(uint16_t device_id) {
    auto ret = KnownNuvotonChips()->find(device_id);
    if (ret != KnownNuvotonChips()->end()) {
        return &ret->second;
    } else {
        return nullptr;
    }
}
