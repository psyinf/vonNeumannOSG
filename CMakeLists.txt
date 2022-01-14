cmake_minimum_required(VERSION 3.16)
include(D:/private/develop/vcpkg/scripts/buildsystems/vcpkg.cmake)
set(CMAKE_TOOLCHAIN_FILE D:/private/develop/vcpkg/scripts/buildsystems/vcpkg.cmake)
set(OSG_DIR  D:/private/develop/vcpkg/packages/osg_x64-windows_rwd)
project(testProj)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_DEBUG_POSTFIX _d)
set(CMAKE_RELWITHDEBINFO_POSTFIX _rd)

find_package(nlohmann_json CONFIG REQUIRED)
FIND_PACKAGE (OpenSceneGraph REQUIRED COMPONENTS osgUtil osgDB osgText osgGA osgFX osgSim osgViewer)
FIND_PACKAGE (OpenThreads REQUIRED )
find_path(PLOG_INCLUDE_DIRS "plog/Appenders/AndroidAppender.h")
if(WIN32)
    add_compile_definitions(WINDOWS=1)
endif ()


add_subdirectory(src)

