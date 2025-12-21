cmake_minimum_required(VERSION 3.15)
project(EU4dll VERSION 1.33.3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Platform detection
if(WIN32)
    set(PLATFORM_WINDOWS TRUE)
    set(LIB_SUFFIX ".dll")
elseif(APPLE)
    set(PLATFORM_MACOS TRUE)
    set(LIB_SUFFIX ".dylib")
elseif(UNIX)
    set(PLATFORM_LINUX TRUE)
    set(LIB_SUFFIX ".so")
endif()

# Find Boost
find_package(Boost REQUIRED)

# Common includes
include_directories(
    ${Boost_INCLUDE_DIRS}
)

# Platform abstraction layer
add_subdirectory(platform)

# Plugin (32-bit on Windows, not needed on macOS)
if(PLATFORM_WINDOWS)
    add_subdirectory(Plugin)
endif()

# Plugin64 (main library)
add_subdirectory(Plugin64)

# d3d9 wrapper (Windows only)
if(PLATFORM_WINDOWS)
    add_subdirectory(d3d9)
endif()

# version checker (Windows only)
if(PLATFORM_WINDOWS)
    add_subdirectory(version)
endif()
