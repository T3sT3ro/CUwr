cmake_minimum_required(VERSION 3.8)
project(CUwr)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES Uwr/W5/ONP/wyrazenie.c Uwr/W5/ONP/wyrazenie.c Uwr/W5/ONP/main.c Uwr/W5/ONP/wyrazenie.h Uwr/W5/ONP/stack.h Uwr/W5/ONP/stack.c)
add_executable(Cuwr ${SOURCE_FILES})