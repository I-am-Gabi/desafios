cmake_minimum_required(VERSION 3.3)
project(desafios)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES 2unity/2237_Containers.cpp)
add_executable(desafios ${SOURCE_FILES})
