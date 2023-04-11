cmake_minimum_required(VERSION 3.24)
project(SIMULATOR)

set(CMAKE_CXX_STANDARD 17)

add_executable(SIMULATOR main.cpp gui.h gui.c main.c simHandler.c aaa.c)
