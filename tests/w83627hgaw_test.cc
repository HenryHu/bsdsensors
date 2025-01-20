#include "nuvoton_chip.h"
#include "nuvoton_test.h"

namespace bsdsensors {
namespace {

const std::map<uint8_t, uint8_t> kTestRegisters = {
    // Device ID
    {0x20, 0x52},
    {0x21, 0x17},
    // Activated
    {0x30, 0x01},
    // Access base address
    {0x60, 0x01},
    {0x61, 0x00},
};

struct W83627HGAWTest : public ::testing::Test {
  void SetUp() override {
      auto port_io = CreateFakePortIO(kTestRegisters);
      chip = CreateNuvotonChip(std::move(port_io));
  }

  std::unique_ptr<NuvotonChip> chip;
};

TEST_F(W83627HGAWTest, Detect) {
    EXPECT_TRUE(chip->Detect());
}

}
}

