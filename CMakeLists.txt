# CMakeLists.txt Template

## Project Configuration
cmake_minimum_required(VERSION 3.12)  # Minimum version of CMake required
project(P2PNode VERSION 1.0.0 LANGUAGES CXX)  # Project name and version

## Compiler Configuration
set(CMAKE_CXX_STANDARD 20)  # Set C++ standard to use
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # Require the specified standard

# Set the output directory for binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

## Source Files
set(SOURCE_FILES
    src/main.cpp
    # Add additional source files here
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

