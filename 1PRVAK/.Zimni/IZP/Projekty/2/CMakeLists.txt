cmake_minimum_required(VERSION 3.6)
project(Projekt2)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -Wextra -Werror")

set(SOURCE_FILES proj2.c proj2.c proj2.c)
add_executable(Projekt2 ${SOURCE_FILES})
target_link_libraries(Projekt2 m)