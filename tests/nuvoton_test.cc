#include "nuvoton_chip.h"
#include "nuvoton_test.h"

#include "testdata.pb.h"

#include "test_util.h"

#include <google/protobuf/text_format.h>
#include <google/protobuf/util/message_differencer.h>

namespace bsdsensors {
namespace {

HmDataTable GetTestHmData(const TestData& test_data) {
    HmDataTable result;
    for (const auto& [bank, bank_data] : test_data.hm_data()) {
        result[bank].insert(bank_data.values().begin(), bank_data.values().end());
    }
    return result;
}

struct NuvotonTest : public ::testing::Test {
  void SetUp() override {
      TestData test_data = LoadTestInput();
      auto port_io = CreateFakePortIO(
              {test_data.registers().begin(), test_data.registers().end()},
              GetTestHmData(test_data));
      chip = CreateNuvotonChip(std::move(port_io));
  }

  std::unique_ptr<NuvotonChip> chip;
};

TEST_F(NuvotonTest, Detect) {
    EXPECT_TRUE(chip->Detect());
}

TEST_F(NuvotonTest, Dump) {
    std::stringstream ss;
    ASSERT_TRUE(chip->Detect());
    chip->DumpInfo(ss);
}

TEST_F(NuvotonTest, Sensors) {
    ASSERT_TRUE(chip->Detect());
    SensorsProto sensors;
    ASSERT_TRUE(chip->GetSensorValues(&sensors).ok());

    SensorsProto expected_sensors = LoadTestOutputSensors();

    EXPECT_TRUE(google::protobuf::util::MessageDifferencer::ApproximatelyEquals(
                sensors, expected_sensors));
}
}
}

