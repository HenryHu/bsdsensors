/*
 * nct5569d.cc
 * Copyright (C) 2020 Henry Hu
 *
 * Distributed under terms of the 3-clause BSD license.
 */

#include "nuvoton_chip_info.h"

namespace bsdsensors {

std::map<NuvotonTempSource, uint8_t> kNCT5569DTempSource{
    {kSourceCPUTIN, 1},       {kSourceAUXTIN2, 2},
    {kSourceAUXTIN0, 3},      {kSourceAUXTIN1, 4},
    {kSourcePECI0, 5},        {kSourcePECI1, 6},
    {kSourceVirtualTemp1, 7}, {kSourceVirtualTemp2, 7},
    {kSourceVirtualTemp3, 7},
};

const NuvotonChipInfo kNCT5569D = {
    0x1061,
    "NCT5569D",
    /*vendor_id_addr=*/{0, 0x4F},
    // Fan speed info
    {
        {"SYSFAN",
         // RPM
         /*rpm_high=*/{0, 0x3A},
         /*rpm_low=*/{0, 0x3B},
         /*count=*/{},
         /*divisor=*/{},
         // Fan Control
         NuvotonFanControlInfo{/*mode_select=*/{1, 0x02, {7, 4}},
                               /*output_value_write=*/{1, 0x09},
                               /*support_dc=*/false,
                               /*output_type=*/{},
                               /*output_value_read=*/{kFastAccessBank, 0x4C},
                               /*temp_source=*/{1, 0x00, {4, 0}},
                               /*temp_value_int=*/{kFastAccessBank, 0x19},
                               /*temp_value_frac=*/{},
                               // Smart Fan I
                               {false},
                               // Smart Fan IV
                               {true,
                                // Control points
                                {{/*temp=*/{1, 0x21}, /*power=*/{1, 0x27}},
                                 {/*temp=*/{1, 0x22}, /*power=*/{1, 0x28}},
                                 {/*temp=*/{1, 0x23}, /*power=*/{1, 0x29}},
                                 {/*temp=*/{1, 0x24}, /*power=*/{1, 0x2A}}}}}},
        {"CPUFAN",
         /*rpm_high=*/{0, 0x3C},
         /*rpm_low=*/{0, 0x3D},
         /*count=*/{},
         /*divisor=*/{},
         // Fan Control
         NuvotonFanControlInfo{/*mode_select=*/{2, 0x02, {7, 4}},
                               /*output_value_write=*/{2, 0x09},
                               /*support_dc=*/false,
                               /*output_type=*/{},
                               /*output_value_read=*/{kFastAccessBank, 0x4D},
                               /*temp_source=*/{2, 0x00, {4, 0}},
                               /*temp_value_int=*/{kFastAccessBank, 0x1A},
                               /*temp_value_frac=*/{},
                               // Smart Fan I
                               {false},
                               // Smart Fan IV
                               {true,
                                // Control points
                                {{/*temp=*/{2, 0x21}, /*power=*/{2, 0x27}},
                                 {/*temp=*/{2, 0x22}, /*power=*/{2, 0x28}},
                                 {/*temp=*/{2, 0x23}, /*power=*/{2, 0x29}},
                                 {/*temp=*/{2, 0x24}, /*power=*/{2, 0x2A}}}}}},
        {"AUXFAN",
         /*rpm_high=*/{0, 0x3E},
         /*rpm_low=*/{0, 0x3F},
         /*count=*/{},
         /*divisor=*/{},
         // Fan Control
         NuvotonFanControlInfo{/*mode_select=*/{3, 0x02, {7, 4}},
                               /*output_value_write=*/{3, 0x09},
                               /*support_dc=*/false,
                               /*output_type=*/{},
                               /*output_value_read=*/{kFastAccessBank, 0x4E},
                               /*temp_source=*/{3, 0x00, {4, 0}},
                               /*temp_value_int=*/{kFastAccessBank, 0x1B},
                               /*temp_value_frac=*/{},
                               // Smart Fan I
                               {false},
                               // Smart Fan IV
                               {true,
                                // Control points
                                {{/*temp=*/{3, 0x21}, /*power=*/{3, 0x27}},
                                 {/*temp=*/{3, 0x22}, /*power=*/{3, 0x28}},
                                 {/*temp=*/{3, 0x23}, /*power=*/{3, 0x29}},
                                 {/*temp=*/{3, 0x24}, /*power=*/{3, 0x2A}}}}}},
    },
    // Temp sensors
    kNCT5569DTempSource,
    {
        {"SMIOVT1", /*val_int=*/{kFastAccessBank, 0x1C}, /*val_frac=*/{},
         /*has_peci_frac=*/false, /*can_select=*/true,
         /*select=*/{6, 0x21, {2, 0}}},
        {"SMIOVT2", /*val_int=*/{kFastAccessBank, 0x1D}, /*val_frac=*/{},
         /*has_peci_frac=*/false, /*can_select=*/true,
         /*select=*/{6, 0x22, {2, 0}}},
        {"CPUTIN", {kFastAccessBank, 0x10}},
        {"AUXTIN2", {kFastAccessBank, 0x11}},
        {"AUXTIN0", {kFastAccessBank, 0x12}},
        {"AUXTIN1", {kFastAccessBank, 0x13}},
        {"SYSTIN", {kFastAccessBank, 0x14}},
        {"PECI0", {kFastAccessBank, 0x52}},
        {"PECI1", {kFastAccessBank, 0x54}},
    },
    // Volts
    {
        {"Vcore", {kFastAccessBank, 0x00}, 2.0},
        {"Vin0", {kFastAccessBank, 0x01}},
        {"AVcc", {kFastAccessBank, 0x02}, 2.0},
        {"3Vcc", {kFastAccessBank, 0x03}, 2.0},
        {"Vin1", {kFastAccessBank, 0x04}},
        {"Vtt", {kFastAccessBank, 0x05}},
        {"3Vsb", {kFastAccessBank, 0x06}, 2.0},
        {"Vbat", {kFastAccessBank, 0x07}},
        {"Vin4", {kFastAccessBank, 0x08}},
        {"Vin2", {kFastAccessBank, 0x09}},
        {"Vin3", {kFastAccessBank, 0x0A}},
    }};

RegisterChip<NuvotonChipInfo> kRegisterNCT5569D(kNCT5569D);

}  // namespace bsdsensors

