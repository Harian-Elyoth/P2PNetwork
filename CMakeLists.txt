# CMakeLists.txt Template

## Project Configuration
cmake_minimum_required(VERSION 3.12)  # Minimum version of CMake required
project(P2PNode VERSION 1.0.0 LANGUAGES CXX)  # Project name and version

## Compiler Configuration
set(CMAKE_CXX_STANDARD 20)  # Set C++ standard to use
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # Require the specified standard

# Set the output directory for binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Set the output compiler flags
set(CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -std=c++20 -Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
option(DEBUG "Build with debug information" OFF) # OFF by default
if(DEBUG)
    message("Building with debug information")
    add_compile_options(-g)
else()
    message("Building without debug information")
    add_compile_options(-O3)
endif()

## Source Files
file(GLOB_RECURSE SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc  # Add your source files here
)

## Executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})  # Define the executable

## Include Directories
target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include  # Add your include directories here
)

## Link Libraries
target_link_libraries(${PROJECT_NAME}
    # Add any libraries you want to link with your executable
)

