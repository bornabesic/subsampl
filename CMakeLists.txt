cmake_minimum_required(VERSION 3.1.0)
project(subsampl VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_FLAGS_RELEASE "-O3")

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

option(BUILD_PYTHON_BINDINGS OFF)
option(BUILD_EXAMPLES OFF)

message("Build type: ${CMAKE_BUILD_TYPE}")
message("Python bindings: ${BUILD_PYTHON_BINDINGS}")
message("Tests: ${BUILD_TESTS}")

add_subdirectory(external/)

include_directories(include/)
add_subdirectory(src/)

if (BUILD_EXAMPLES)
    add_subdirectory(examples/)
endif ()
