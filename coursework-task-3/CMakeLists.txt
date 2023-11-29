cmake_minimum_required(VERSION 3.10)
project(calculator)

set(SOURCES main.c calculator.c)

add_library(calculator STATIC ${SOURCES})

add_executable(calculator main.c)
target_link_libraries(calculator calculator)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
