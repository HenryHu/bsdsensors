cmake_minimum_required (VERSION 3.16)

# metadata

project(bsdsensors)

set (bsdsensors_VERSION_MAJOR 0)
set (bsdsensors_VERSION_MINOR 1)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

find_package(protobuf CONFIG REQUIRED)
find_package(gflags REQUIRED)
find_package(glog REQUIRED)

# config

configure_file (
    "${PROJECT_SOURCE_DIR}/config.h.in"
    "${PROJECT_BINARY_DIR}/config.h"
    )

include_directories("${PROJECT_BINARY_DIR}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

# subdirs

add_subdirectory(lib)
add_subdirectory(include)
add_subdirectory(proto)

include_directories ("${PROJECT_SOURCE_DIR}/include")
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# main executable

add_executable(${PROJECT_NAME}-bin src/main.cc)
set_target_properties(${PROJECT_NAME}-bin
    PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME}-bin
    ${PROJECT_NAME}
    ${PROJECT_NAME}-protos
    protobuf::libprotobuf
    gflags
    glog::glog
    )

# install

install(TARGETS ${PROJECT_NAME}-bin DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/config.h"
    DESTINATION include/${PROJECT_NAME})

# package

include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE
    "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set (CPACK_PACKAGE_VERSION_MAJOR "${bsdsensors_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${bsdsensors_VERSION_MINOR}")
include (CPack)

