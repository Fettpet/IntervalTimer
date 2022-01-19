cmake_minimum_required(VERSION 3.21)

OPTION(BUILD_INTERVAL_TESTS "Build the tests" ON)

if(${BUILD_INTERVAL_TESTS})
    include(../third_party/googletest.cmake)

    find_package(Qt6 6.2 COMPONENTS Test REQUIRED)

    add_executable(UnitTests
        Intervaltimer/intervaltimer/Interval.test.cpp
        Intervaltimer/intervaltimer/Plan.test.cpp
        Intervaltimer/intervaltimer/PlanIterator.test.cpp
        Intervaltimer/intervaltimer/PlanModel.test.cpp
        Intervaltimer/intervaltimer/PlanRunner.test.cpp
        Intervaltimer/intervaltimer/Timer.test.cpp
        Intervaltimer/intervaltimer/main.test.cpp
    )
    target_link_libraries(UnitTests
        gtest
        IntervaltimerPlugin
        Intervaltimer
        Qt::Test)
    add_test(UnitTests UnitTests)
endif()
