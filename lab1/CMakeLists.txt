cmake_minimum_required(VERSION 3.10)

project(CircularBuffer)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-fprofile-arcs -ftest-coverage")

set(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")

add_subdirectory(googletest)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runTests tests/tests.cpp CircularBuffer.h) 

target_link_libraries(runTests gtest gtest_main)
