cmake_minimum_required(VERSION 3.8)
project(CUwr)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_FLAGS "${CMAKE_CSS_FLAGS} -Wall -Wextra -Werror")

set(SOURCE_FILES Uwr/W10/ONP.c)

include_directories("Uwr/utils")

add_executable(CUwr ${SOURCE_FILES})