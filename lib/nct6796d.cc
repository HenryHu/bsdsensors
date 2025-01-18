/*
 * nct6796d.cc
 * Copyright (C) 2025 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "nuvoton_chip_info.h"

namespace bsdsensors {

std::map<NuvotonTempSource, uint8_t> kNCT6796DTempSource{
        {kSourceSYSTIN, 1},
        {kSourceCPUTIN, 2},
        {kSourceAUXTIN0, 3},
        {kSourceAUXTIN1, 4},
        {kSourceAUXTIN2, 5},
        {kSourceAUXTIN3, 6},
        {kSourceAUXTIN4, 7},
        {kSourceSMBUSMASTER0, 8},
        {kSourceSMBUSMASTER1, 9},
        {kSourcePECI0, 16},
        {kSourcePECI1, 17},
        {kSourcePCHCPUMAX, 18},
        {kSourcePCH, 19},
        {kSourcePCHCPU, 20},
        {kSourcePCHMCH, 21},
        {kSourceDIM0, 22},
        {kSourceDIM1, 23},
        {kSourceDIM2, 24},
        {kSourceDIM3, 25},
        {kSourceBYTE0, 26},
        {kSourceBYTE1, 27},
        {kSourcePECI0Calib, 28},
        {kSourcePECI1Calib, 29},
        {kSourceVirtualTemp1, 31},
};

const NuvotonChipInfo kNCT6796D = {
    0xD42B,
    "NCT6796D",
    /*vendor_id_addr=*/{0, 0x4F},
    // Fan speed info
    {

    },
    // Temp sensors
    kNCT6796DTempSource,
    {
        {"SMIOVT1", /*val_int=*/{0, 0x27}, /*val_frac=*/{},
         /*has_peci_frac=*/false, /*can_select=*/true,
         /*select=*/{6, 0x21, {4, 0}}},
        {"SMIOVT2", /*val_int=*/{1, 0x50}, /*val_frac=*/{},
         /*has_peci_frac=*/false, /*can_select=*/true,
         /*select=*/{6, 0x22, {4, 0}}},
        {"SMIOVT3", /*val_int=*/{6, 0x70}, /*val_frac=*/{},
         /*has_peci_frac=*/false, /*can_select=*/true,
         /*select=*/{0xC, 0x26, {4, 0}}},
        {"SMIOVT4", /*val_int=*/{6, 0x72}, /*val_frac=*/{},
         /*has_peci_frac=*/false, /*can_select=*/true,
         /*select=*/{0xC, 0x27, {4, 0}}},
        {"SMIOVT5", /*val_int=*/{6, 0x74}, /*val_frac=*/{},
         /*has_peci_frac=*/false, /*can_select=*/true,
         /*select=*/{0xC, 0x28, {4, 0}}},
        {"SMIOVT6", /*val_int=*/{6, 0x76}, /*val_frac=*/{},
         /*has_peci_frac=*/false, /*can_select=*/true,
         /*select=*/{0xC, 0x29, {4, 0}}},
        {"SMIOVT7", /*val_int=*/{6, 0x78}, /*val_frac=*/{},
         /*has_peci_frac=*/false, /*can_select=*/true,
         /*select=*/{0xC, 0x2A, {4, 0}}},
        {"SMIOVT8", /*val_int=*/{6, 0x7A}, /*val_frac=*/{},
         /*has_peci_frac=*/false, /*can_select=*/true,
         /*select=*/{0xC, 0x2B, {4, 0}}},
        {"SYSTIN", {4, 0x90}},
        {"CPUTIN", {4, 0x91}},
        {"AUXTIN0", {4, 0x92}},
        {"AUXTIN1", {4, 0x93}},
        {"AUXTIN2", {4, 0x94}},
        {"AUXTIN3", {4, 0x95}},
        {"PECI0Calibration", {4, 0xF4}},
        {"PECI1Calibration", {4, 0xF5}},
        {"PCH_CPU_MAX", {4, 0x00}},
        {"PCH", {4, 0x01}},
        {"PCH_CPU", {4, 0x02}, {4, 0x03, {7, 2}}, true},
        {"MCH", {4, 0x04}},
        {"DIM0", {4, 0x05}},
        {"DIM1", {4, 0x06}},
        {"DIM2", {4, 0x07}},
        {"DIM3", {4, 0x08}},
        {"TSI0", {4, 0x09}, {4, 0x0A, {7, 5}}},
        {"TSI1", {4, 0x0B}, {4, 0x0C, {7, 5}}},
        {"BYTE0", {4, 0x19}},
        {"BYTE1", {4, 0x1A}},
    },
    // Volts
    {
        {"Vcore", {4, 0x80}},
        {"Vin1", {4, 0x81}},
        {"AVsb", {4, 0x82}},
        {"3Vcc", {4, 0x83}},
        {"Vin0", {4, 0x84}},
        {"Vin8", {4, 0x85}},
        {"Vin4", {4, 0x86}},
        {"3Vsb", {4, 0x87}},
        {"Vbat", {4, 0x88}},
        {"Vtt", {4, 0x89}},
        {"Vin5", {4, 0x8A}},
        {"Vin6", {4, 0x8B}},
        {"Vin2", {4, 0x8C}},
        {"Vin3", {4, 0x8D}},
        {"Vin7", {4, 0x8E}},
        {"Vin9", {4, 0x8F}},
    }
};

RegisterChip<NuvotonChipInfo> kRegisterNCT6796D(kNCT6796D);

}
