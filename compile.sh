#!/bin/bash

DEBUG_OPTION=""
if [ "$1" == "-g" ]; then
    echo "Debug mode enabled."
    DEBUG_OPTION="-DDEBUG=ON"
fi

# Verify the existence of the 'build/' directory
if [ ! -d "build/" ]; then
    echo "Error: The 'build/' directory does not exist. Creating it..."
    mkdir build || { echo "Error: Unable to create the 'build/' directory."; exit 1; }
fi

# Change to the 'build/' directory
pushd build || { echo "Error: Unable to change to the 'build/' directory."; exit 1; }

# Run CMake
cmake $DEBUG_OPTION .. || { echo "Error: CMake configuration failed."; popd; exit 1; }

# Run Make
make || { echo "Error: Compilation failed."; popd; exit 1; }

# Return to the previous directory
popd

echo "Build successful! The executable is located in 'bin/'."