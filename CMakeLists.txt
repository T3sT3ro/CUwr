cmake_minimum_required(VERSION 3.8)
project(CUwr)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES Uwr/W8/fileFilter.c)

include_directories("Uwr/utils")

add_executable(CUwr ${SOURCE_FILES})

configure_file(Uwr/W8/tests/test_random_1 test_random_1)
configure_file(Uwr/W8/tests/test_bufferOverflow_1 test_bufferOverflow_1)