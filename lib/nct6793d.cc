/*
 * nct6793d.cc
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "nuvoton_chip_info.h"

const NuvotonChipInfo kNCT6793D = {
    0xd121,
    "NCT6793D",
    {0, 0x4F},
    // Fan speed info
    {
        {"SYSFAN",
         // RPM
         {4, 0xC0},
         {4, 0xC1},
         // Fan Control
         {{1, 0x02, {7, 4}},
          {1, 0x09},
          true,
          {0, 0x04, {0}},
          {0, 0x01},
          {1, 0x00, {4, 0}},
          {0, 0x73},
          {0, 0x74, {7}},
          // Smart Fan I
          {false},
          // Smart Fan IV
          {true,
           // Control points
           {{{1, 0x21}, {1, 0x27}},
            {{1, 0x22}, {1, 0x28}},
            {{1, 0x23}, {1, 0x29}},
            {{1, 0x24}, {1, 0x2A}}}}}},
        {"CPUFAN",
         {4, 0xC2},
         {4, 0xC3},
         // Fan Control
         {{2, 0x02, {7, 4}},
          {2, 0x09},
          true,
          {0, 0x04, {1}},
          {0, 0x03},
          {2, 0x00, {4, 0}},
          {0, 0x75},
          {0, 0x76, {7}},
          // Smart Fan I
          {false},
          // Smart Fan IV
          {true,
           // Control points
           {{{2, 0x21}, {2, 0x27}},
            {{2, 0x22}, {2, 0x28}},
            {{2, 0x23}, {2, 0x29}},
            {{2, 0x24}, {2, 0x2A}}}}}},
        {"AUXFAN0",
         {4, 0xC4},
         {4, 0xC5},
         {{3, 0x02, {7, 4}},
          {3, 0x09},
          true,
          {0, 0x04, {2}},
          {0, 0x11},
          {3, 0x00, {4, 0}},
          {0, 0x77},
          {0, 0x78, {7}},
          // Smart Fan I
          {false},
          // Smart Fan IV
          {true,
           // Control points
           {{{3, 0x21}, {3, 0x27}},
            {{3, 0x22}, {3, 0x28}},
            {{3, 0x23}, {3, 0x29}},
            {{3, 0x24}, {3, 0x2A}}}}}},
        {"AUXFAN1",
         {4, 0xC6},
         {4, 0xC7},
         {{8, 0x02, {7, 4}},
          {8, 0x09},
          true,
          {0, 0x04, {3}},
          {0, 0x13},
          {8, 0x00, {4, 0}},
          {0, 0x79},
          {0, 0x7A, {7}},
          // Smart Fan I
          {false},
          // Smart Fan IV
          {true,
           // Control points
           {{{3, 0x21}, {3, 0x27}},
            {{3, 0x22}, {3, 0x28}},
            {{3, 0x23}, {3, 0x29}},
            {{3, 0x24}, {3, 0x2A}}}}}},
        {"AUXFAN2",
         {4, 0xC8},
         {4, 0xC9},
         {{9, 0x02, {7, 4}},
          {9, 0x09},
          true,
          {0, 0x04, {4}},
          {0, 0x15},
          {9, 0x00, {4, 0}},
          {0, 0x7B},
          {0, 0x7C, {7}},
          // Smart Fan I
          {false},
          // Smart Fan IV
          {true,
           // Control points
           {{{3, 0x21}, {3, 0x27}},
            {{3, 0x22}, {3, 0x28}},
            {{3, 0x23}, {3, 0x29}},
            {{3, 0x24}, {3, 0x2A}}}}}},
        {"AUXFAN3",
         {4, 0xCA},
         {4, 0xCB},
         {{10, 0x02, {7, 4}},
          {10, 0x09},
          true,
          {0, 0x04, {5}},
          {0, 0x17},
          {10, 0x00, {4, 0}},
          {0, 0x7D},
          {0, 0x7E, {7}},
          // Smart Fan I
          {false},
          // Smart Fan IV
          {true,
           // Control points
           {{{3, 0x21}, {3, 0x27}},
            {{3, 0x22}, {3, 0x28}},
            {{3, 0x23}, {3, 0x29}},
            {{3, 0x24}, {3, 0x2A}}}}}},
    },
    // Temp sensors
    {
        {"SMIOVT1", false, {0, 0x27}, {0, 0}, false, true, {6, 0x21, {4, 0}}},
        {"SMIOVT2",
         true,
         {1, 0x50},
         {1, 0x51, {7}},
         false,
         true,
         {6, 0x22, {4, 0}}},
        {"SYSTIN", false, {4, 0x90}},
        {"CPUTIN", false, {4, 0x91}},
        {"AUXTIN0", false, {4, 0x92}},
        {"AUXTIN1", false, {4, 0x93}},
        {"AUXTIN2", false, {4, 0x94}},
        {"AUXTIN3", false, {4, 0x95}},
        {"PECI", true, {7, 0x20}, {7, 0x21, {1, 0}}, true},
    },
    // Volts
    {
        {"Vcore", {4, 0x80}, 2.0},
        {"AVcc", {4, 0x82}, 2.0},
        {"3Vcc", {4, 0x83}, 2.0},
        {"3Vsb", {4, 0x87}, 2.0},
        {"Vbat", {4, 0x88}, 2.0},
        {"Vtt", {4, 0x89}},
        {"Vin0", {4, 0x84}},
        {"Vin1", {4, 0x81}},
        {"Vin2", {4, 0x8C}},
        {"Vin3", {4, 0x8D}},
        {"Vin4", {4, 0x86}},
        {"Vin5", {4, 0x8A}},
        {"Vin6", {4, 0x8B}},
        {"Vin7", {4, 0x8E}},
        {"Vin8", {4, 0x85}},
    }};

RegisterNuvotonChip kRegisterNCT6793D(kNCT6793D);
