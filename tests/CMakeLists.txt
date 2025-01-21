enable_testing()

add_library(test_util SHARED fake_port_io.cc test_util.cc)
target_link_libraries(test_util bsdsensors)

set(CHIPS w83627hgaw)

foreach(CHIP IN LISTS CHIPS)
    add_executable(${CHIP}_test nuvoton_test.cc test_main.cc)
    target_link_libraries(${CHIP}_test bsdsensors GTest::gtest test_util)
    add_test(NAME ${CHIP}Test COMMAND ${CHIP}_test
        --testdata_path ${CMAKE_SOURCE_DIR}/testdata
        --testin_filename ${CHIP}_in.pb.txt
        --testout_sensors_filename ${CHIP}_sensors.pb.txt
    )
endforeach()
