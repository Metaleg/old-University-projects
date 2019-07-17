cmake_minimum_required(VERSION 3.13)
project(Lutsiv_lab2)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 17)

add_executable(Lutsiv_lab2 main.cpp)
target_link_libraries( Lutsiv_lab2 ${OpenCV_LIBS} )












