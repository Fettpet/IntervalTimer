cmake_minimum_required(VERSION 3.21)

add_library(intervalltimer STATIC)
set(CMAKE_CXX_STANDARD 20)

target_include_directories(intervalltimer PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
)

target_sources(intervalltimer PRIVATE
    intervall/intervall.cpp
    intervall/intervall.h
    intervall/plan.cpp
    intervall/plan.h
)
