enable_testing()

add_executable(w83627hgaw_test w83627hgaw_test.cc)
target_link_libraries(w83627hgaw_test bsdsensors GTest::gtest_main)
add_test(NAME w83627hgawTest COMMAND w83627hgaw_test)
