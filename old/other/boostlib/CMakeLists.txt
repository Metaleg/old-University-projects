cmake_minimum_required(VERSION 3.10)
project(boostlib)

set(CMAKE_CXX_STANDARD 14)

add_executable(boostlib xmlparser.cpp hana.cpp main.cpp)