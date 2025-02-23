# Mandatory CMake version requirement
cmake_minimum_required(VERSION 3.30)

# The name of the project
project(OS)

# This project uses C++ 23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# For the C++ LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# This searches for all C/C++ files
file(GLOB_RECURSE SRC_FILES
  ${PROJECT_SOURCE_DIR}/src/*.cc
  ${PROJECT_SOURCE_DIR}/src/*.c
)

# This defines the OS executable
add_executable(${PROJECT_NAME} ${SRC_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
)

# This enables the testing suite via ctest
enable_testing()

# This searches for all test files

