#!/bin/bash

PRESET=${1:-debug}
TARGET=${2:-all}
BUILD_DIR="build/$PRESET"

mkdir -p build

cmake --preset $PRESET

if [[ $? -ne 0 ]]; then
    echo "Error: CMake configuration failed for preset $PRESET"
    exit 1
fi

cmake --build "$BUILD_DIR" --target $TARGET

if [[ $? -ne 0 ]]; then
    echo "Error: Build failed for target $TARGET"
    exit 1
fi

echo "Build succeeded for target '$TARGET' using preset '$PRESET'"