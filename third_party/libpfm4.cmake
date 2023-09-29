# third-party module: libpmf4
FetchContent_Declare(
        libpfm4
        GIT_REPOSITORY https://github.com/wcohen/libpfm4.git
        GIT_TAG        f3c229370d402c2f1d8e3de858de63a3784db68a # release-4.8.0
)
FetchContent_MakeAvailable(libpfm4)