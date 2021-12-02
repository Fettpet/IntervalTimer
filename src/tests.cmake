cmake_minimum_required(VERSION 3.21)

OPTION(BUILD_INTERVALL_TESTS "Build the tests" ON)

if(${BUILD_INTERVALL_TESTS})
    include(../third_party/googletest.cmake)

    add_executable(UnitTests
        intervall/intervall.test.cpp)
    target_link_libraries(UnitTests gtest_main intervalltimer)
    add_test(UnitTests UnitTests)
endif()
