cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 20)

find_package(Qt6 6.2 COMPONENTS Quick  REQUIRED)

qt_add_library(IntervaltimerLib STATIC)

target_include_directories(IntervaltimerLib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Interval>
)

qt_add_qml_module(IntervaltimerLib
    URI Intervaltimer
    VERSION 1.0
    OUTPUT_DIRECTORY Intervaltimer
    QML_FILES
        qml/Interval.qml
        qml/Plan.qml
    SOURCES
        Interval/Interval.cpp
        Interval/Interval.h
        Interval/IntervalFromJson.h
        Interval/IntervalFromJson.cpp
        Interval/IntervallToJson.h
        Interval/IntervallToJson.cpp
        Interval/Plan.cpp
        Interval/Plan.h
        Interval/PlanModel.cpp
        Interval/PlanModel.h
)

