cmake_minimum_required(VERSION 3.10)
project(CoralisProject)

# Set C standard (optional)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g3")

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add the source code
add_subdirectory(src)

# Add the tests
#add_subdirectory(tests)
