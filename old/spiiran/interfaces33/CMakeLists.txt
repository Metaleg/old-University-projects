cmake_minimum_required(VERSION 3.13)
project(interfaces33)

set(CMAKE_CXX_STANDARD 17)

add_executable(interfaces33 imu.cpp imu.h main.cpp)