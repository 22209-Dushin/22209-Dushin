cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)


project(WordCounter)


set(SOURCE_FILES
        counter.cpp
        main.cpp
        counter.h)

add_executable(WordCounter ${SOURCE_FILES})
