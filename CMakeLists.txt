cmake_minimum_required(VERSION 3.10.3)

project(comm_algo)

set(CMAKE_BUILD_TYPE "Debug")
add_definitions(-std=c++11)

include_directories(src/common)
include_directories(src/array)
include_directories(src/linklist)
include_directories(src/sort)
include_directories(src/queue)
include_directories(src/cache)
include_directories(src/unittest)

file(GLOB_RECURSE SOURCE_FILE_LISTS src/*.h src/*.cc src/*.hpp src/*.c src/*.cpp)

add_executable(comm_algo ${SOURCE_FILE_LISTS})