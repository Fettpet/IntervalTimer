cmake_minimum_required(VERSION 3.21)

OPTION(BUILD_INTERVAL_TESTS "Build the tests" ON)

if(${BUILD_INTERVAL_TESTS})
    include(../third_party/googletest.cmake)

    find_package(Qt6 6.2 COMPONENTS Test REQUIRED)

    add_executable(UnitTests
        Interval/Interval.test.cpp
        Interval/Plan.test.cpp
        Interval/PlanIterator.test.cpp
        Interval/PlanModel.test.cpp
        Interval/PlanRunner.test.cpp
    )
    target_link_libraries(UnitTests gtest_main IntervaltimerLib Qt::Test)
    add_test(UnitTests UnitTests)
endif()
