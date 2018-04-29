/*
 * nuvoton_chip.h
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#ifndef __BSDSENSORS_NUVOTON_CHIP_H__
#define __BSDSENSORS_NUVOTON_CHIP_H__

#include "chip.h"
#include "status.h"

#include <memory>

class NuvotonChip : public Chip {
   public:
    bool Detect() override = 0;
    virtual void DumpInfo() = 0;

    virtual Status Enter() = 0;
    virtual Status Exit() = 0;
};

std::unique_ptr<NuvotonChip> CreateNuvotonChip();

#endif  // __BSDSENSORS_NUVOTON_CHIP_H__
