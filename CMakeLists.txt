cmake_minimum_required(VERSION 3.19)
project(carsim)

set(CMAKE_CXX_STANDARD 20)

option(CARSIM_BUILD_TESTS "Build tests" ON)

include(FetchContent)

set(THREEPP_BUILD_TESTS OFF)
set(THREEPP_BUILD_EXAMPLES OFF)
FetchContent_Declare(
        threepp
        GIT_REPOSITORY https://github.com/markaren/threepp.git
        GIT_TAG 49c14a7445e3870ad2307f626076a05b0c915d6b
)
FetchContent_MakeAvailable(threepp)

add_subdirectory(src)

add_executable(carsim main.cpp)
target_link_libraries(carsim PRIVATE carlib)

if (CARSIM_BUILD_TESTS)
    FetchContent_Declare(
            Catch2
            GIT_REPOSITORY https://github.com/catchorg/Catch2.git
            GIT_TAG v3.7.0
    )
    FetchContent_MakeAvailable(Catch2)

    enable_testing()
    add_subdirectory(tests)
endif ()


######### Emscripten #######
if (DEFINED EMSCRIPTEN)

    set(LINK_FLAGS " --bind -sUSE_GLFW=3 -sGL_DEBUG=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 \
    -sFULL_ES3 -sASSERTIONS -sALLOW_MEMORY_GROWTH -sWASM=1")

    set_target_properties("demo"
            PROPERTIES SUFFIX ".html"
            LINK_FLAGS "${LINK_FLAGS}"
    )

endif ()
###########################
