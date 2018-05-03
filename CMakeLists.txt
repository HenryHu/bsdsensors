cmake_minimum_required (VERSION 2.8)

project(bsdsensors)

set (bsdsensors_VERSION_MAJOR 0)
set (bsdsensors_VERSION_MINOR 1)

configure_file (
    "${PROJECT_SOURCE_DIR}/config.h.in"
    "${PROJECT_BINARY_DIR}/config.h"
    )

include_directories("${PROJECT_BINARY_DIR}")

add_definitions('-Wall')
add_definitions('-std=c++14')

add_subdirectory(lib)
include_directories ("${PROJECT_SOURCE_DIR}/include")

add_executable(${PROJECT_NAME}-bin src/main.cc)
set_target_properties(${PROJECT_NAME}-bin
    PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME}-bin ${PROJECT_NAME})
