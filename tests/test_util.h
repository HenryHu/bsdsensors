#ifndef __BSDSENSORS_TESTS_TEST_UTIL_H_
#define __BSDSENSORS_TESTS_TEST_UTIL_H_

#include "testdata.pb.h"
#include "sensors.pb.h"

namespace bsdsensors {

TestData LoadTestInput();

SensorsProto LoadTestOutputSensors();
}

#endif //  __BSDSENSORS_TESTS_TEST_UTIL_H_
