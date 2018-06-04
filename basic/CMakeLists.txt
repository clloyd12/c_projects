cmake_minimum_required(VERSION 3.5.1)
project (basic)
set (CMAKE_BUILD_TYPE "Debug")

# include .h files for the project
include_directories(inc)

file(GLOB SOURCES "src/*.c")

set (MAIN_SRC src/main.c src/fileops.c src/btree.c)
#set (FILEOPS_SRC src/fileops.c)
set (STRINGOPS_SRC src/stringops.c)
set (FUNCPOINTERS_SRC src/func_pointers.c)
set (MAIN_EXECUTABLE "main")
#set (FILEOPS_EXECUTABLE "fileops")
set (STRINGOPS_EXECUTABLE "stringops")
set (FUNCPOINTERS_EXECUTABLE "functors")
add_executable(${MAIN_EXECUTABLE} ${MAIN_SRC})
#add_executable(${FILEOPS_EXECUTABLE} ${FILEOPS_SRC})
add_executable(${STRINGOPS_EXECUTABLE} ${STRINGOPS_SRC})
add_executable(${FUNCPOINTERS_EXECUTABLE} ${FUNCPOINTERS_SRC})

# add math library
target_link_libraries(${MAIN_EXECUTABLE} m)

set(CMAKE_C_STANDARD "11")
# add warnings
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -H -fno-stack-protector -isystem /usr/include -Wall -Wextra -Wno-unused-parameter -pthread")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -H -isystem /usr/include -Wall -Wextra -Wno-unused-parameter -pthread")

message(STATUS "CMAKE Flags are ${CMAKE_C_FLAGS}")

# set (TUTORIAL_SRC src/tutorial.c src/foobar.c)
# Add this for YouCompleteMe
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
