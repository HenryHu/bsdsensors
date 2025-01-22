#include "test_util.h"

#include <gflags/gflags.h>
#include <gtest/gtest.h>
#include <glog/logging.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/text_format.h>

#include <fcntl.h>

#include "testdata.pb.h"

DECLARE_string(testdata_path);
DECLARE_string(testin_filename);
DECLARE_string(testout_sensors_filename);

namespace bsdsensors {
namespace {

template <typename ProtoType>
ProtoType LoadTestProto(const std::string& path) {
    int fin = open(path.c_str(), O_RDONLY);
    CHECK(fin != -1);
    auto input = std::unique_ptr<google::protobuf::io::ZeroCopyInputStream>(new google::protobuf::io::FileInputStream(fin));

    ProtoType proto;
    CHECK(google::protobuf::TextFormat::Parse(input.get(), &proto));

    close(fin);
    return proto;
}
}

TestData LoadTestInput() {
    return LoadTestProto<TestData>(
            FLAGS_testdata_path + "/" + FLAGS_testin_filename);
}

SensorsProto LoadTestOutputSensors() {
    return LoadTestProto<SensorsProto>(
            FLAGS_testdata_path + "/" + FLAGS_testout_sensors_filename);
}

void SaveTestOutputSensors(const SensorsProto& proto) {
    const std::string path = FLAGS_testdata_path + "/" + FLAGS_testout_sensors_filename;
    int fout = open(path.c_str(), O_RDWR | O_CREAT, 0644);
    CHECK(fout != -1);
    auto output = std::unique_ptr<google::protobuf::io::ZeroCopyOutputStream>(new google::protobuf::io::FileOutputStream(fout));

    CHECK(google::protobuf::TextFormat::Print(proto, output.get()));

    output.reset();
    close(fout);
}

}
