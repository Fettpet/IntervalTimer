cmake_minimum_required(VERSION 3.21)

add_library(IntervaltimerLib STATIC)
set(CMAKE_CXX_STANDARD 20)

target_include_directories(IntervaltimerLib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
)

target_link_libraries(IntervaltimerLib
    Qt6::Core)

target_sources(IntervaltimerLib PRIVATE
    interval/interval.cpp
    interval/interval.h
    interval/plan.cpp
    interval/plan.h
)
