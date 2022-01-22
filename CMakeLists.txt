cmake_minimum_required(VERSION 3.15)
project(testProj VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_DEBUG_POSTFIX _d)
set(CMAKE_RELWITHDEBINFO_POSTFIX _rd)

# Run conan install automatically, or display warning if conan is not installed
include(cmake/conan_config.cmake)


if(WIN32)
    add_compile_definitions(WINDOWS=1)
endif ()

add_subdirectory(src)