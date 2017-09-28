#specify minimum version for CMake
cmake_minimum_required(VERSION 3.8)

#project name
project(DocumentSearcher)

set(CMAKE_CXX_STANDARD 17)
set(SOURCE_FILES main.cpp TxtSearcher.cpp TxtSearcher.h TxtProcessor.cpp TxtProcessor.h)

add_executable(DocumentSearcher ${SOURCE_FILES})