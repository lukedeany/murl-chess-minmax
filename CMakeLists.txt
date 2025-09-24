cmake_minimum_required(VERSION 3.22...4.0)

set(CMAKE_CXX_STANDARD 20)

project(Chess_minmax)

SET(SOURCES src/main.cpp src/Position.cpp)

add_executable(Chess_Minmax ${SOURCES})
