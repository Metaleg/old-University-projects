cmake_minimum_required(VERSION 3.12)
project(madgwick)

set(CMAKE_CXX_STANDARD 17)

add_executable(madgwick main.cpp cmake-build-debug/madgwick.cpp cmake-build-debug/madgwick.h)