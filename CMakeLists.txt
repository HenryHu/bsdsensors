cmake_minimum_required (VERSION 2.8)

project(bsdsensors)

set (bsdsensors_VERSION_MAJOR 0)
set (bsdsensors_VERSION_MINOR 1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 14)

configure_file (
    "${PROJECT_SOURCE_DIR}/config.h.in"
    "${PROJECT_BINARY_DIR}/config.h"
    )

include_directories("${PROJECT_BINARY_DIR}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_subdirectory(lib)
add_subdirectory(include)
include_directories ("${PROJECT_SOURCE_DIR}/include")

add_executable(${PROJECT_NAME}-bin src/main.cc)
set_target_properties(${PROJECT_NAME}-bin
    PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME}-bin ${PROJECT_NAME})

install(TARGETS ${PROJECT_NAME}-bin DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/config.h"
    DESTINATION include/${PROJECT_NAME})

include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE
    "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set (CPACK_PACKAGE_VERSION_MAJOR "${bsdsensors_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${bsdsensors_VERSION_MINOR}")
include (CPack)

