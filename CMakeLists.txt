cmake_minimum_required(VERSION 3.8)

set(project_name sisaenv)
project(${project_name} C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

file(GLOB Sources "src/*.c")
add_executable(${project_name} ${Sources})

