cmake_minimum_required(VERSION 3.13)
project(TEA C)

set(CMAKE_C_STANDARD 99)

add_executable(TEA main.c redBlackTree.c redBlackTree.h)