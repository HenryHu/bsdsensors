file(GLOB SRCS *.cc *.h)
add_library(${PROJECT_NAME} SHARED ${SRCS})
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-protos)

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
