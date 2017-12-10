cmake_minimum_required(VERSION 3.8)
project(CUwr)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES Uwr/utils/deque.c Uwr/W7/Labirynt.c)

include_directories("Uwr/utils")

add_executable(CUwr ${SOURCE_FILES})