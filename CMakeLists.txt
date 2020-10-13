cmake_minimum_required(VERSION 3.17)
project(databaseDesign)

set(CMAKE_CXX_STANDARD 17)

add_executable(databaseDesign memory-pool.h memory-pool.cpp main.cpp)