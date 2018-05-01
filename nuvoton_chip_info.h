/*
 * nuvoton_chip_info.h
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#ifndef __BSDSENSORS_NUVOTON_CHIP_INFO_H__
#define __BSDSENSORS_NUVOTON_CHIP_INFO_H__

#include <map>
#include <cstdint>
#include <string>
#include <vector>

#include "nuvoton_chip.h"

struct NuvotonSmartFanInfo {
    bool available;
};

struct NuvotonSmartFan4ControlPointInfo {
    NuvotonChip::AddressType temp;
    NuvotonChip::AddressType power;
};

struct NuvotonSmartFan4Info {
    bool available;
    std::vector<NuvotonSmartFan4ControlPointInfo> control_points;
};

enum NuvotonFanControlMode {
    kManualMode = 0,
    kThermalCruise = 1,
    kSpeedCruise = 2,
    kSmartFan4 = 4,
};

struct NuvotonFanControlInfo {
    NuvotonChip::AddressType mode_select, output_value_write, output_type,
        output_value_read;
    NuvotonSmartFanInfo smart_fan;
    NuvotonSmartFan4Info smart_fan4;
};

struct NuvotonFanInfo {
    std::string name;
    NuvotonChip::AddressType rpm_high, rpm_low;
    NuvotonFanControlInfo control;
};

struct NuvotonTempInfo {
    std::string name;
    bool has_frac_part;
    NuvotonChip::AddressType val_int, val_frac;
    bool has_peci_frac;
    bool can_select;
    NuvotonChip::AddressType select;
};

struct NuvotonVoltInfo {
    std::string name;
    NuvotonChip::AddressType addr;
    // Result = raw value * alpha + beta
    double alpha = 1.0, beta = 0.0;
};

struct NuvotonChipInfo {
    std::string name;
    NuvotonChip::AddressType vendor_id_addr;
    std::vector<NuvotonFanInfo> fans;
    std::vector<NuvotonTempInfo> temps;
    std::vector<NuvotonVoltInfo> volts;
};

const std::map<uint16_t, NuvotonChipInfo> kKnownNuvotonChips = {
    {0xd121,
     {"NCT6793D",
      {0, 0x4F},
      // Fan speed info
      {
          {"SYSFAN",
           // RPM
           {4, 0xC0},
           {4, 0xC1},
           // Fan Control
           {{1, 0x02},
            {1, 0x09},
            {0, 0x04},
            {0, 0x01},
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
           {{2, 0x02},
            {2, 0x09},
            {0, 0x04},
            {0, 0x03},
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
           {{3, 0x02},
            {3, 0x09},
            {0, 0x04},
            {0, 0x11},
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
           {{8, 0x02},
            {8, 0x09},
            {0, 0x04},
            {0, 0x13},
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
           {{9, 0x02},
            {9, 0x09},
            {0, 0x04},
            {0, 0x15},
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
           {{10, 0x02},
            {10, 0x09},
            {0, 0x04},
            {0, 0x17},
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
          {"SMIOVT1", false, {0, 0x27}, {0, 0}, false, true, {6, 0x21}},
          {"SMIOVT2", true, {1, 0x50}, {1, 0x51}, false, true, {6, 0x22}},
          {"SYSTIN", false, {4, 0x90}, {1, 0x51}},
          {"CPUTIN", false, {4, 0x91}, {1, 0x51}},
          {"AUXTIN0", false, {4, 0x92}, {1, 0x51}},
          {"AUXTIN1", false, {4, 0x93}, {1, 0x51}},
          {"AUXTIN2", false, {4, 0x94}, {1, 0x51}},
          {"AUXTIN3", false, {4, 0x95}, {1, 0x51}},
          {"PECI", true, {7, 0x20}, {7, 0x21}, true},
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
      }}}};

#endif  // __BSDSENSORS_NUVOTON_CHIP_INFO_H__
