cmake_minimum_required(VERSION 3.21)

OPTION(BUILD_INTERVAL_TESTS "Build the tests" ON)

if(${BUILD_INTERVAL_TESTS})
    include(../third_party/googletest.cmake)

    add_executable(UnitTests
        interval/interval.test.cpp
        interval/plan.test.cpp
    )
    target_link_libraries(UnitTests gtest_main intervaltimer)
    add_test(UnitTests UnitTests)
endif()
