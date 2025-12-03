cmake_minimum_required(VERSION 3.10)
project(StudentManagementSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(src)

# Source files
set(SOURCES
    src/main.cpp
    src/core/Logger.cpp
    src/service/StudentService.cpp
    src/ui/CLI.cpp
)

# Executable
add_executable(StudentManagementSystem ${SOURCES})

# Threading support
find_package(Threads REQUIRED)
target_link_libraries(StudentManagementSystem Threads::Threads)
