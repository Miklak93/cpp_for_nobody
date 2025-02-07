# Set required CMake version
cmake_minimum_required(VERSION 3.22)

# Set the project name and version
project(Studies VERSION 1.0)

# To allow includes like path/to/header.h instead of just header.h
# Example:
# target_include_directories(Target INTERFACE ${PROJECT_ROOT_DIR})
#
# If you want to have direct include, without path (like includes have),
# replace it with ${CMAKE_CURRENT_SOURCE_DIR}:
# target_include_directories(Target INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
set(PROJECT_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(PROJECT_CMAKE_DIR ${PROJECT_ROOT_DIR}/cmake)
set(ALGORITHMS_ROOT_DIR ${PROJECT_ROOT_DIR}/algorithms_and_structures)
set(DESIGN_PATTERNS_ROOT_DIR ${PROJECT_ROOT_DIR}/design_patterns)

# To decide if tests should be build or not. The default configuration is "Debug" so tests are normally on
# unless decided otherwise - see comments below. Also it is important to have this setting defined
# before "Release"/"Debug" configuration to prevent override the ENABLE_TESTS value.
option(ENABLE_TESTS "Enable building and running tests" ON)

# Include additional sources
include(${PROJECT_CMAKE_DIR}/StrictFlags.cmake)

# Specify C++ standard and add strict compiler flags
add_library(CompilerFlags INTERFACE)
target_compile_features(CompilerFlags INTERFACE cxx_std_20)
enable_strict_flags(CompilerFlags)

# Should be removed, but somehow previous line does not work
set(CMAKE_CXX_STANDARD 20)

# Automatically disable tests for release builds
#
# Release build command from the 'build' directory
# cmake .. -DCMAKE_BUILD_TYPE=Release && make
#
# Debug build command from the 'build' directory
# cmake .. -DCMAKE_BUILD_TYPE=Debug && make
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    message("Release build triggered")
    set(ENABLE_TESTS OFF CACHE BOOL "Disable building and running tests" FORCE)
# For other cases keep tests enabled
else()
    set(ENABLE_TESTS ON CACHE BOOL "Enable building and running tests" FORCE)
endif()

# Subdirectories
add_subdirectory(algorithms_and_structures)
add_subdirectory(design_patterns)

# Tests
# Option ENABLE_TESTS can be adjusted from the command line
#
# Build tests with ENABLE_TESTS on from the 'build' directory:
# cmake .. -DENABLE_TESTS=ON && make
#
# Build tests with ENABLE_TESTS off from the 'build' directory:
# cmake .. -DENABLE_TESTS=OFF && make
#
if (ENABLE_TESTS)
    # Fetch googletest library
    include(FetchContent)
    FetchContent_Declare(
      googletest
      # Pick the last release from googletest github page.
      URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    )
    FetchContent_MakeAvailable(googletest)

    # Enable testing
    enable_testing()

    # Add test subdirectory
    add_subdirectory(test)
endif()

# Find additional libraries
# To include boost perform "sudo apt install libboost-all-dev -y" at first
find_package(Boost REQUIRED thread)

# To be able to use std::execution stuff
find_package(TBB REQUIRED)

