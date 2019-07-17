cmake_minimum_required(VERSION 3.12)
project(rts2 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")
add_executable(rts2 main.c)