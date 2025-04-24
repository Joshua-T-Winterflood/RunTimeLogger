cmake_minimum_required(VERSION 3.16.0)
project(RunTimeLogger VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

file(GLOB PROJECT_SRC
    "${CMAKE_SOURCE_DIR}/*.cpp"
    "${CMAKE_SOURCE_DIR}/*.h"
)

add_executable(RunTimeLogger ${PROJECT_SRC})