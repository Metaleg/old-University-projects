cmake_minimum_required(VERSION 3.12)
project(rts3 C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lrt")
add_executable(rts3 main.c)