file(GLOB SRCS *.cc *.h)
include_directories ("${PROJECT_SOURCE_DIR}/include")
add_library(${PROJECT_NAME} ${SRCS})

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
