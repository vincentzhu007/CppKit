# global setting for third party software
include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED OFF)

add_subdirectory(googletest)
add_subdirectory(benchmark)
add_subdirectory(flatbuffers)