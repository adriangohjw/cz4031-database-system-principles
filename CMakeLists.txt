cmake_minimum_required(VERSION 3.17)
project(databaseDesign)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static-libstdc++")
add_executable(memory-pool.h memory-pool.cpp main.cpp BplusTree.cpp)
