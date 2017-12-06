cmake_minimum_required(VERSION 3.8)
project(CUwr)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES Uwr/W7/BinaryTree.c Uwr/W7/BinaryTree.h Uwr/W7/BST_test.c)
add_executable(CUwr ${SOURCE_FILES})