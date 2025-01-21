#include "nuvoton_chip.h"
#include "nuvoton_test.h"

#include <google/protobuf/text_format.h>
#include <google/protobuf/util/message_differencer.h>

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

constexpr char kExpectedSensors[] = R"pb(
fans {
  name: "FAN1"
  speed {
    value: 5273
  }
  control {
    current_method: "Manual"
    current_percent: 1
    methods {
      name: "Manual"
      nuvoton_method {
        manual_params {
          percent: 64.705882352941174
        }
      }
    }
    temp_source: "Unknown"
  }
}
fans {
  name: "FAN2"
  speed {
    value: 5232
  }
  control {
    current_method: "Manual"
    current_percent: 1
    methods {
      name: "Manual"
      nuvoton_method {
        manual_params {
          percent: 64.705882352941174
        }
      }
    }
    temp_source: "Unknown"
  }
}
fans {
  name: "FAN3"
  speed {
    value: 5192
  }
  control {
    current_method: "Manual"
    current_percent: 1
    methods {
      name: "Manual"
      nuvoton_method {
        manual_params {
          percent: 64.705882352941174
        }
      }
    }
    temp_source: "Unknown"
  }
}
temperatures {
  name: "VTIN1"
  value: 49
}
temperatures {
  name: "VTIN2"
  value: 50
}
temperatures {
  name: "VTIN3"
  value: 51
}
voltages {
  name: "VcoreA"
  value: 0.512
}
voltages {
  name: "VcoreB"
  value: 0.528
}
voltages {
  name: "3.3Vin"
  value: 0.544
}
voltages {
  name: "5Vin"
  value: 0.94080000000000008
}
voltages {
  name: "12Vin"
  value: 2.1888
}
voltages {
  name: "-12Vin"
  value: -11.86712
}
voltages {
  name: "-5Vin"
  value: -5.80088
}
voltages {
  name: "5Vsb"
  value: 2.1504
}
voltages {
  name: "Vbat"
  value: 1.296
}
name: "nuvoton"
)pb";

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
    std::stringstream ss;
    ASSERT_TRUE(chip->Detect());
    chip->DumpInfo(ss);
}

TEST_F(W83627HGAWTest, Sensors) {
    ASSERT_TRUE(chip->Detect());
    SensorsProto sensors;
    ASSERT_TRUE(chip->GetSensorValues(&sensors).ok());

    SensorsProto expected_sensors;
    ASSERT_TRUE(google::protobuf::TextFormat::ParseFromString(
                kExpectedSensors, &expected_sensors));

    EXPECT_TRUE(google::protobuf::util::MessageDifferencer::ApproximatelyEquals(
                sensors, expected_sensors));
}
}
}

