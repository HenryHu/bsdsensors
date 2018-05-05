/*
 * nct6102d.cc
 * Copyright (C) 2018 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "nuvoton_chip_info.h"

namespace bsdsensors {

const NuvotonChipInfo kNCT6102D = {0x1061,
                                   "NCT6102D",
                                   {0, 0xFE},
                                   // Fan speed info
                                   {
                                       {"SYSFAN",
                                        // RPM
                                        {0, 0x30},
                                        {0, 0x31},
                                        // Fan Control
                                        {{1, 0x13, {7, 4}},
                                         {1, 0x19},
                                         true,
                                         {0, 0xF3, {0}},
                                         {0, 0x4A},
                                         {1, 0x10, {4, 0}},
                                         {0, 0x18},
                                         {0, 0x1B, {0}},
                                         // Smart Fan I
                                         {false},
                                         // Smart Fan IV
                                         {true,
                                          // Control points
                                          {{{1, 0x60}, {1, 0x64}},
                                           {{1, 0x61}, {1, 0x65}},
                                           {{1, 0x62}, {1, 0x66}},
                                           {{1, 0x63}, {1, 0x67}}}}}},
                                       {"CPUFAN",
                                        {0, 0x32},
                                        {0, 0x33},
                                        // Fan Control
                                        {{1, 0x23, {7, 4}},
                                         {1, 0x29},
                                         true,
                                         {0, 0xF3, {1}},
                                         {0, 0x4B},
                                         {1, 0x20, {4, 0}},
                                         {0, 0x19},
                                         {0, 0x1B, {1}},
                                         // Smart Fan I
                                         {false},
                                         // Smart Fan IV
                                         {true,
                                          // Control points
                                          {{{1, 0x70}, {1, 0x74}},
                                           {{1, 0x71}, {1, 0x75}},
                                           {{1, 0x72}, {1, 0x76}},
                                           {{1, 0x73}, {1, 0x77}}}}}},
                                       {"AUXFAN",
                                        {0, 0x34},
                                        {0, 0x35},
                                        {{1, 0x33, {7, 4}},
                                         {1, 0x39},
                                         true,
                                         {0, 0xF3, {2}},
                                         {0, 0x4C},
                                         {1, 0x30, {4, 0}},
                                         {0, 0x1A},
                                         {0, 0x1B, {2}},
                                         // Smart Fan I
                                         {false},
                                         // Smart Fan IV
                                         {true,
                                          // Control points
                                          {{{1, 0x80}, {1, 0x84}},
                                           {{1, 0x81}, {1, 0x85}},
                                           {{1, 0x82}, {1, 0x86}},
                                           {{1, 0x83}, {1, 0x87}}}}}},
                                   },
                                   // Temp sensors
                                   {
                                       {"SMIOVT1",
                                        true,
                                        {0, 0x10},
                                        {0, 0x16, {0}},
                                        false,
                                        true,
                                        {0, 0xB0, {4, 0}}},
                                       {"SMIOVT2",
                                        true,
                                        {0, 0x11},
                                        {0, 0x16, {1}},
                                        false,
                                        true,
                                        {0, 0xB1, {4, 0}}},
                                       {"SMIOVT3",
                                        true,
                                        {0, 0x12},
                                        {0, 0x16, {2}},
                                        false,
                                        true,
                                        {0, 0xB2, {4, 0}}},
                                       {"SMIOVT4",
                                        true,
                                        {0, 0x13},
                                        {0, 0x16, {3}},
                                        false,
                                        true,
                                        {0, 0xB3, {4, 0}}},
                                       {"SMIOVT5",
                                        true,
                                        {0, 0x14},
                                        {0, 0x16, {4}},
                                        false,
                                        true,
                                        {0, 0xB4, {4, 0}}},
                                       {"SMIOVT6",
                                        true,
                                        {0, 0x15},
                                        {0, 0x16, {5}},
                                        false,
                                        true,
                                        {0, 0xB5, {4, 0}}},
                                       {"SYSTIN", false, {3, 0x0C}},
                                       {"CPUTIN", false, {3, 0x0D}},
                                       {"AUXTIN", false, {3, 0x0E}},
                                       {"PCH_CPU_MAX", false, {0, 0x50}},
                                       {"PCH", false, {0, 0x51}},
                                       {"PCH_CPU", false, {0, 0x52}},
                                       {"MCH", false, {0, 0x54}},
                                       {"DIM0", false, {0, 0x55}},
                                       {"DIM1", false, {0, 0x56}},
                                       {"DIM2", false, {0, 0x57}},
                                       {"DIM3", false, {0, 0x58}},
                                       {"PECI", false, {0, 0x6B}},
                                   },
                                   // Volts
                                   {
                                       {"Vcore", {0, 0x00}, 2.0},
                                       {"AVcc", {0, 0x02}, 2.0},
                                       {"3Vcc", {0, 0x03}, 2.0},
                                       {"3Vsb", {0, 0x07}, 2.0},
                                       {"Vbat", {0, 0x08}},
                                       {"Vin0", {0, 0x01}},
                                       {"Vin1", {0, 0x04}},
                                       {"Vin2", {0, 0x05}},
                                   }};

RegisterChip<NuvotonChipInfo> kRegisterNCT6102D(kNCT6102D, &NuvotonChips);

}  // namespace bsdsensors
