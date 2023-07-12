# import external: protobuf

include(FetchContent)

# Turn off protobuf tests.
set(protobuf_BUILD_TESTS OFF)

FetchContent_Declare(
        protobuf
        GIT_REPOSITORY https://github.com/protocolbuffers/protobuf.git
        GIT_TAG 2c5fa078d8e86e5f4bd34e6f4c9ea9e8d7d4d44a # version 4.23.4
)

FetchContent_MakeAvailable(protobuf)