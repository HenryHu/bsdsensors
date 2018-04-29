/*
 * main.cc
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "nuvoton_chip.h"
#include <iostream>
#include <unistd.h>

using namespace std;

int main() {
    auto chip = CreateNuvotonChip();
    if (chip->Detect()) {
    }
}
