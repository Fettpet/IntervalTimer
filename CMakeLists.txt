cmake_minimum_required(VERSION 3.21)

project(Intervaltimer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

enable_testing()
add_subdirectory(third_party)
add_subdirectory(src)
