cmake_minimum_required(VERSION 3.0)

project(TextMining)

# C++14 and extra flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra -std=c++1y -O3 -g")

# Sets library output directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

include_directories(
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/tests
        ${CMAKE_SOURCE_DIR}/app
)

# Adds source directory
add_subdirectory(src)
add_subdirectory(tests)

add_executable(TextMiningCompiler app/main_compiler.cpp)
target_link_libraries(TextMiningCompiler tree)
add_executable(TextMiningApp app/main_app.cpp)
target_link_libraries(TextMiningApp tree)
