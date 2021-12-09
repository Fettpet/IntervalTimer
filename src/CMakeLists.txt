cmake_minimum_required(VERSION 3.21)


set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick Core REQUIRED)

OPTION(BUILD_INTERVAL_APPLICATON "Build the Application" ON)

include(tests.cmake)
include(interval.cmake)

if(${BUILD_INTERVAL_APPLICATON})
    qt_add_executable(appIntervaltimer
        main.cpp
        PlanModel.h
        PlanModel.cpp
    )

    add_subdirectory(qml)

    target_compile_definitions(appIntervaltimer
        PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
    target_link_libraries(appIntervaltimer
        PRIVATE Qt6::Quick IntervaltimerLib IntervalTimerQMLplugin)
endif()
