enable_testing()

add_library(test_util SHARED fake_port_io.cc test_util.cc)
target_link_libraries(test_util bsdsensors)
add_executable(nuvoton_test nuvoton_test.cc test_main.cc)
target_link_libraries(nuvoton_test bsdsensors GTest::gtest test_util)

set(CHIPS w83627hgaw nct6796d w83667hg_p5q w83667hg_p6t_se)
foreach(CHIP IN LISTS CHIPS)
    add_test(NAME ${CHIP}_test COMMAND nuvoton_test
        --testdata_path ${CMAKE_SOURCE_DIR}/testdata
        --testin_filename ${CHIP}_in.pb.txt
        --testout_sensors_filename ${CHIP}_sensors.pb.txt
    )
endforeach()
