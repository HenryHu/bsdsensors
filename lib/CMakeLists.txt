file(GLOB SRCS *.cc *.h)
include_directories ("${PROJECT_SOURCE_DIR}/include")
add_library(libbsdsensors ${SRCS})

