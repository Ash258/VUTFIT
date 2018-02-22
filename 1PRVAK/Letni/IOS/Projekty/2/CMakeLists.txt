cmake_minimum_required(VERSION 3.7)
project(IOS2)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99 -Wall -Wextra -Werror -pedantic")

set(SOURCE_FILES proj2.c proj2.h)
add_executable(IOS2 ${SOURCE_FILES})
