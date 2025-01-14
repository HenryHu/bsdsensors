file(GLOB PROTOS *.proto)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(${PROJECT_NAME}-protos OBJECT ${PROTOS})
target_link_libraries(${PROJECT_NAME}-protos PUBLIC protobuf::libprotobuf)

set(PROTO_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}")

protobuf_generate(
    TARGET ${PROJECT_NAME}-protos
    IMPORT_DIRS "${CMAKE_CURRENT_LIST_DIR}"
    PROTOC_OUT_DIR "${PROTO_BINARY_DIR}")

target_include_directories(${PROJECT_NAME}-protos PUBLIC "$<BUILD_INTERFACE:${PROTO_BINARY_DIR}>")
