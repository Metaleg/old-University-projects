cmake_minimum_required(VERSION 3.13)
project(linux_daemon C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")

add_executable(linux_daemon daemon.c work_with_config.h work_with_config.c)