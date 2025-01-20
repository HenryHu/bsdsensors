enable_testing()

add_library(test_util SHARED fake_port_io.cc)
target_link_libraries(test_util bsdsensors)

add_executable(w83627hgaw_test w83627hgaw_test.cc test_main.cc)
target_link_libraries(w83627hgaw_test bsdsensors GTest::gtest test_util)
add_test(NAME w83627hgawTest COMMAND w83627hgaw_test)
