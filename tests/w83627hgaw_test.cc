#include "nuvoton_chip.h"
#include "nuvoton_test.h"

namespace bsdsensors {
namespace {

const ControlRegisterTable kTestRegisters = {
    // Device ID
    {0x20, 0x52},
    {0x21, 0x17},
    // Activated
    {0x30, 0x01},
    // Access base address
    {0x60, 0x01},
    {0x61, 0x00},
};

const HmDataTable kTestHmData = {
    {0, {
            {0x4F, 0xA3},
            {0x58, 0xC1},
            // FAN1
            {0x28, 0x80},
            {0x5D, 0x01},
            {0x47, 0x55},
            {0x5A, 0xFF},
            // FAN2
            {0x29, 0x81},
            {0x5B, 0xFF},
            // FAN3
            {0x2A, 0x82},
            {0x11, 0xFF},
            {0x4B, 0x44},
            // VTIN1
            {0x27, 0x31},
            {0x54, 0x00},
            // Volts
            {0x20, 0x20},
            {0x21, 0x21},
            {0x22, 0x22},
            {0x23, 0x23},
            {0x24, 0x24},
            {0x25, 0x25},
            {0x26, 0x26},
        } },
    {1, {
            // VTIN2
            {0x50, 0x32},
            {0x51, 0x00},
        } },
    {2, {
            // VTIN3
            {0x50, 0x33},
            {0x51, 0x00},
        } },
    {5, {
            {0x50, 0x50},
            {0x51, 0x51},
        } },
    {0x80,
        {
            {0x4F, 0x5C},
        } }
};

struct W83627HGAWTest : public ::testing::Test {
  void SetUp() override {
      auto port_io = CreateFakePortIO(kTestRegisters, kTestHmData);
      chip = CreateNuvotonChip(std::move(port_io));
  }

  std::unique_ptr<NuvotonChip> chip;
};

TEST_F(W83627HGAWTest, Detect) {
    EXPECT_TRUE(chip->Detect());
}

TEST_F(W83627HGAWTest, Dump) {
    ASSERT_TRUE(chip->Detect());
    chip->DumpInfo(std::cerr);
}


}
}

