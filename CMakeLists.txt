cmake_minimum_required(VERSION 3.29)
project(CLIIIII)

set(CMAKE_CXX_STANDARD 20)

# Collect source files
file(GLOB SOURCES "src/*.cpp")

# Create an executable
add_executable(CLIIIII ${SOURCES})

# Include the headers directory
target_include_directories(CLIIIII PRIVATE include)

# Pass the output directory as a compile-time definition
target_compile_definitions(CLIIIII PRIVATE OUTPUT_DIR="${CMAKE_BINARY_DIR}/output")
