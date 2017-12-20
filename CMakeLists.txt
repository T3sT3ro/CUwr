cmake_minimum_required(VERSION 3.8)
project(CUwr)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_FLAGS "${CMAKE_CSS_FLAGS} -Wall -Wextra -Werror")


find_package(Curses REQUIRED)

include_directories(${CURSES_LIBRARIES} "Uwr/utils")

set(SOURCE_FILES Uwr/W9/ball.c)

add_executable(CUwr ${SOURCE_FILES})

target_link_libraries(CUwr ${CURSES_LIBRARIES})
