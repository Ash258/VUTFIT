cmake_minimum_required(VERSION 3.6)
project(Projekt1)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wextra -Werror -Wall")

set(SOURCE_FILES proj1.c test.c proj1.c)
add_executable(Projekt1 ${SOURCE_FILES})