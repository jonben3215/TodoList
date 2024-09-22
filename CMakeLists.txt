# Set minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(TODO VERSION 1.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable - specify your source file(s) here
add_executable(todo hashTask.cpp)

# Add a custom target to run the executable after build
add_custom_target(RunTodo
    COMMAND ${CMAKE_COMMAND} -E echo "Running Todo executable..."
    COMMAND Todo
    DEPENDS Todo
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Building and running Todo..."
)
