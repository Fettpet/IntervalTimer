cmake_minimum_required(VERSION 3.21)

OPTION(BUILD_INTERVALL_TESTS "Build the tests" ON)

if(${BUILD_INTERVALL_TESTS})
    include(../third_party/googletest.cmake)
endif()
