cmake_minimum_required(VERSION 3.8)
project(CUwr)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES Uwr/W2/sameline.c)
add_executable(Cuwr ${SOURCE_FILES})