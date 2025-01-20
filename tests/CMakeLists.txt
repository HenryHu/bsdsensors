add_executable(nuvoton_test nuvoton_test.cc)
target_link_libraries(nuvoton_test bsdsensors)
add_test(NAME nuvotonTest COMMAND nuvoton_test)
