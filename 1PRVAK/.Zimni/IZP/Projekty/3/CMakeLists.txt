cmake_minimum_required(VERSION 3.6)
project(Projekt3)

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -Wextra -Werror -DNDEBUG")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -Wextra -Werror -NDEBUG")

set(SOURCE_FILES proj3.c cosi.c)
add_executable(Projekt3 ${SOURCE_FILES})
target_link_libraries(Projekt3 m)