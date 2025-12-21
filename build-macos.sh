#!/bin/bash
# Build script for macOS

set -e

echo "=== EU4dll macOS Build Script ==="

# Check if CMake is installed
if ! command -v cmake &> /dev/null; then
    echo "Error: CMake is not installed. Please install it using: brew install cmake"
    exit 1
fi

# Check if Boost is installed
if ! brew list boost &> /dev/null; then
    echo "Warning: Boost might not be installed. Installing via Homebrew..."
    brew install boost
fi

# Create build directory
BUILD_DIR="build"
if [ -d "$BUILD_DIR" ]; then
    echo "Build directory exists. Cleaning..."
    rm -rf "$BUILD_DIR"
fi

mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

# Configure
echo "Configuring project..."
cmake .. -DCMAKE_BUILD_TYPE=Release

# Build
echo "Building project..."
cmake --build . --config Release

echo "=== Build completed successfully ==="
echo "Output: $BUILD_DIR/Plugin64/Plugin64.dylib"
