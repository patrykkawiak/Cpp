cmake_minimum_required(VERSION 3.15)
project(Lesson_1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(Lesson_1 src/main.cpp src/Player.cpp
        include/ComputerPlayer.h
        src/ComputerPlayer.cpp
)