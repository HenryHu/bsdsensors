/*
 * it8772e.cc
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "ite_chip_info.h"

namespace bsdsensors {

ITEChipInfo kIT8772E{
    0x8772,
    "IT8772E",
};

RegisterChip<ITEChipInfo> kRegisterIT8772E(kIT8772E, &ITEChips);

}  // namespace bsdsensors
