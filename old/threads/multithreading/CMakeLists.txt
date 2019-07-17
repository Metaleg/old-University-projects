cmake_minimum_required(VERSION 3.10)
project(multithreading)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")


add_executable(multithreading main.cpp)