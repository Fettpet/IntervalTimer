cmake_minimum_required(VERSION 3.21)

project(Intervaltimer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(QML_IMPORT_PATH ${CMAKE_CURRENT_BINARY_DIR} CACHE STRING "" FORCE)

enable_testing()
add_subdirectory(third_party)
add_subdirectory(src)
