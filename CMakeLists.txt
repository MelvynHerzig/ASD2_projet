cmake_minimum_required(VERSION 3.17)
project(ASD2_projet)

set(CMAKE_CXX_STANDARD 14)

add_executable(ASD2_projet main.cpp)
add_subdirectory(catch2_tests)