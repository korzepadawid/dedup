cmake_minimum_required(VERSION 3.30)
project(dedup C)

set(CMAKE_C_STANDARD 23)

add_executable(dedup main.c
        map.c
        map.h
        sha256.c
        sha256.h)
