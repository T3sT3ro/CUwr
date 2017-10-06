cmake_minimum_required(VERSION 3.8)
project(Cuwr)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES Uwr/W0/narcissistic.c)
add_executable(Cuwr ${SOURCE_FILES})