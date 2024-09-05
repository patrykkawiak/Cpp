cmake_minimum_required(VERSION 3.15)
project(Lesson_1)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_executable(Lesson_1 main.cpp src/Player.cpp
)