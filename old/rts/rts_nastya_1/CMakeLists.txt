cmake_minimum_required(VERSION 3.12)
project(rts_nastya_1 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")

add_executable(rts_nastya_1 main.c)