cmake_minimum_required(VERSION 3.12) 
 
project(CircularBuffer) 
 
set(CMAKE_CXX_STANDARD 17) 
set(CMAKE_CXX_STANDARD_REQUIRED True) 
 
SET(CMAKE_CXX_FLAGS "-fprofile-arcs -ftest-coverage") 
SET(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage") 
 
include(FetchContent) 
FetchContent_Declare( 
    googletest 
    GIT_REPOSITORY https://github.com/google/googletest.git 
    GIT_TAG release-1.11.0 
) 
FetchContent_MakeAvailable(googletest) 
 
include_directories(${CMAKE_CURRENT_SOURCE_DIR}) 
 
add_executable(runTests CircularBuffer.cpp tests.cpp) 
 
add_custom_target(coverage 
        COMMAND gcovr --root=${CMAKE_SOURCE_DIR} --exclude=${CMAKE_SOURCE_DIR}/build --html --html-details -o coverage_report.html 
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR} 
        COMMENT "Generating code coverage report" 
    ) 
add_dependencies(runTests coverage) 
 
target_link_libraries(runTests gtest_main gcov) 
 
enable_testing() 
 
add_test(NAME Lab1Test COMMAND runTests)
