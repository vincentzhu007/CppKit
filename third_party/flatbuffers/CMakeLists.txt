# Third-party library: FlatBuffers

include(FetchContent)

FetchContent_Declare(
        flatbuffers
        GIT_REPOSITORY https://github.com/google/flatbuffers.git
        GIT_TAG acf39ff056df8c9e5bfa32cf6f7b5e6b87a90544 # version 22.12.06
)

FetchContent_MakeAvailable(flatbuffers)