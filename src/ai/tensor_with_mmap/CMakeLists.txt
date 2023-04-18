set(TENSOR_WITH_MMAP_SCHEMA "${CMAKE_CURRENT_LIST_DIR}/tensor_with_mmap.fbs")
set(TENSOR_WITH_MMAP_HEADER tensor_with_mmap_generated.h)
set(TENSOR_WITH_MMAP_DIR ${CMAKE_CURRENT_BINARY_DIR})

add_custom_command(OUTPUT ${TENSOR_WITH_MMAP_HEADER}
        COMMAND flatc --cpp -o ${TENSOR_WITH_MMAP_DIR} ${TENSOR_WITH_MMAP_SCHEMA}
        DEPENDS ${TENSOR_WITH_MMAP_SCHEMA} flatc
        )
add_custom_target(gen_tensor_with_mmap_fbs DEPENDS ${TENSOR_WITH_MMAP_HEADER})

add_executable(tensor_with_mmap_writer tensor_with_mmap_writer.cpp)
target_link_libraries(tensor_with_mmap_writer PRIVATE flatbuffers)
target_include_directories(tensor_with_mmap_writer PRIVATE ${TENSOR_WITH_MMAP_DIR})
add_dependencies(tensor_with_mmap_writer gen_tensor_with_mmap_fbs)

add_executable(tensor_with_mmap_demo tensor_with_mmap_demo.cpp)
target_link_libraries(tensor_with_mmap_demo PRIVATE flatbuffers)
target_include_directories(tensor_with_mmap_demo PRIVATE ${TENSOR_WITH_MMAP_DIR})
add_dependencies(tensor_with_mmap_demo gen_tensor_with_mmap_fbs)
target_link_libraries(tensor_with_mmap_demo PRIVATE aiutils)
