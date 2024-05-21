cmake_minimum_required(VERSION 3.28)
project(search_and_sort)

set(CMAKE_CXX_STANDARD 17)

add_executable(search_and_sort main.cpp
        Utility.cpp
        Utility.h
        List.cpp
        List.h
        Timer.cpp
        Timer.h
        main.h
)
