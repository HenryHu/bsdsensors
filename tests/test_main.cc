#include <gtest/gtest.h>
#include <glog/logging.h>
#include <gflags/gflags.h>

DEFINE_string(testdata_path, "", "test data path");
DEFINE_string(testin_filename, "", "input file name");
DEFINE_string(testout_sensors_filename, "", "expected sensors output file name");

int main(int argc, char **argv) {
    google::InitGoogleLogging(argv[0]);
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    testing::InitGoogleTest(&argc, argv);
    FLAGS_stderrthreshold = 0;

    CHECK(!FLAGS_testdata_path.empty());
    CHECK(!FLAGS_testin_filename.empty());
    CHECK(!FLAGS_testout_sensors_filename.empty());
    return RUN_ALL_TESTS();
}
