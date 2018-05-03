/*
 * chip.h
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#ifndef __BSDSENSORS_CHIP_H__
#define __BSDSENSORS_CHIP_H__

class Chip {
   public:
    virtual ~Chip() {}

    virtual bool Detect() = 0;
};

#endif  // __BSDSENSORS_CHIP_H__
