cmake_minimum_required(VERSION 3.8)
project(CUwr)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Uwr/W3/bignum.c)
add_executable(Cuwr ${SOURCE_FILES})