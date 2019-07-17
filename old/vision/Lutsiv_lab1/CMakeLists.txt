cmake_minimum_required(VERSION 3.12)
project(Lutsiv_lab1)

set(CMAKE_CXX_STANDARD 17)


find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(Lutsiv_lab1 main.cpp)
target_link_libraries( Lutsiv_lab1 ${OpenCV_LIBS} )