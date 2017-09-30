cmake_minimum_required(VERSION 3.5.1)
project (main)

# include .h files for the project
include_directories(inc)

file(GLOB SOURCES "src/*.c")

# add warnings

set (MAIN_SRC src/main.c)
set (MAIN_EXECUTABLE "main")
add_executable(${MAIN_EXECUTABLE} ${MAIN_SRC})

set(CMAKE_C_STANDARD "11")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I/usr/include -I/usr/src/linux-headers-4.4.0-75-generic -Wall -Wextra -Wno-unused-parameter -pthread")
message(STATUS "CMAKE Flags are ${CMAKE_C_FLAGS}")

# set (TUTORIAL_SRC src/tutorial.c src/foobar.c)
# Add this for YouCompleteMe
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


