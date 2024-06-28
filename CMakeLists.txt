cmake_minimum_required(VERSION 3.27)
project(DSA C)

set(CMAKE_C_STANDARD 11)


add_executable(DSA
        main.c
        linked_list/node.c
        utils/read.c
        utils/errors.c
        linked_list/list.c
        utils/read.h
)

target_sources(DSA PRIVATE linked_list/list.c)
