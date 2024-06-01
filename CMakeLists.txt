cmake_minimum_required(VERSION 3.27)
project(DSA C)

set(CMAKE_C_STANDARD 11)
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")

add_executable(DSA
        main.c
        linked_list/node.c
        utils/errors.c
        linked_list/list.c
)

target_sources(DSA PRIVATE linked_list/list.c)
