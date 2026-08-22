cmake_minimum_required(VERSION 3.16)

# ------------------------------------------------------------------
# Project information
# ------------------------------------------------------------------
project(Klarion
    VERSION 0.1.0
    DESCRIPTION "A modern, configurable C++ logging library"
    LANGUAGES CXX
)

# ------------------------------------------------------------------
# Global compiler settings
# ------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Sensible default for single-config generators
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# ------------------------------------------------------------------
# Options
# ------------------------------------------------------------------
option(KLARION_BUILD_EXAMPLES "Build Klarion examples" OFF)
option(KLARION_BUILD_TESTS "Build Klarion tests" OFF)

# ------------------------------------------------------------------
# Testing
# ------------------------------------------------------------------
if(KLARION_BUILD_TESTS)
    enable_testing()
endif()

# ------------------------------------------------------------------
# Dependencies (submodules)
# ------------------------------------------------------------------
add_subdirectory(external/fmt)
add_subdirectory(external/tomlplusplus)

# ------------------------------------------------------------------
# Library
# ------------------------------------------------------------------
add_subdirectory(src)

if(KLARION_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(KLARION_BUILD_TESTS)
    add_subdirectory(tests)
endif()
