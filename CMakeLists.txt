cmake_minimum_required(VERSION 3.9)
project(IntervalMap)

set(CMAKE_CXX_STANDARD 17)

add_library(interval_map INTERFACE
        interval_map.h
)

target_include_directories(interval_map INTERFACE ${CMAKE_CURRENT_LIST_DIR})

add_subdirectory(tests)