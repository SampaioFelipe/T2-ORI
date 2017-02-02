cmake_minimum_required(VERSION 3.5)
project(ArvoreB)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.c ArvoreB.h ArvoreB.c)
add_executable(ArvoreB ${SOURCE_FILES})