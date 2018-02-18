cmake_minimum_required(VERSION 3.8)
project(CUwr)

set(CMAKE_CXX_STANDARD 98)
#set(CMAKE_CXX_FLAGS "${CMAKE_CSS_FLAGS} -Wall -Wextra -Werror")

set(SOURCE_FILES MIA/acm.cpp)

include_directories("Uwr/utils")

add_executable(CUwr ${SOURCE_FILES})