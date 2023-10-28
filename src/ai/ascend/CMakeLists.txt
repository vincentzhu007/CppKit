# lib
file(GLOB ASCEND_DEMO_SRC ascend_env_validator.cpp)
add_library(ascend_demo ${ASCEND_DEMO_SRC})


# test
file(GLOB ASCEND_DEME_TEST_SRC
        ascend_env_validator_test.cpp)

add_executable(ascend_demo_test ${ASCEND_DEME_TEST_SRC})
target_link_libraries(ascend_demo_test PRIVATE gtest gtest_main gmock)
target_link_libraries(ascend_demo_test PRIVATE ascend_demo)



