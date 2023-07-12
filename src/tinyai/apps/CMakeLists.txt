include(FindProtobuf)
protobuf_generate_cpp(PROTO_SRC PROTO_HEADER onnx.proto)
message(STATUS "onnx proto header:" ${PROTO_HEADER})

add_library(onnx_proto OBJECT ${PROTO_HEADER} ${PROTO_SRC})
target_include_directories(onnx_proto PUBLIC ${Protobuf_INCLUDE_DIRS})
target_link_libraries(onnx_proto PUBLIC libprotobuf-lite)

add_executable(print_onnx print_onnx.cpp)
target_include_directories(print_onnx PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(print_onnx PUBLIC onnx_proto)