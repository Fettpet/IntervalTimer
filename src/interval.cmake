cmake_minimum_required(VERSION 3.21)

add_library(intervaltimer STATIC)
set(CMAKE_CXX_STANDARD 20)

target_include_directories(intervaltimer PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
)

target_sources(intervaltimer PRIVATE
    interval/interval.cpp
    interval/interval.h
    interval/plan.cpp
    interval/plan.h
)
