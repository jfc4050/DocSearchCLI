cmake_minimum_required(VERSION 3.8)
project(DocumentSearcher)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp)
add_executable(DocumentSearcher ${SOURCE_FILES})
add_executable(TxtReader TxtReader.cpp)