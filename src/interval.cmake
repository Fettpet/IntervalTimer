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
        qml/IntervalView.qml
        qml/PlanView.qml
        qml/PlanEditorView.qml
        qml/PlanRunningView.qml
    SOURCES
        interval/Interval.cpp
        interval/Interval.h
        interval/IntervalFromJson.h
        interval/IntervalFromJson.cpp
        interval/IntervalToJson.h
        interval/IntervalToJson.cpp
        interval/Plan.cpp
        interval/Plan.h
        interval/PlanIterator.h
        interval/PlanIterator.cpp
        interval/PlanModel.cpp
        interval/PlanModel.h
        interval/PlanFromJson.h
        interval/PlanFromJson.cpp
        interval/PlanRunner.h
        interval/PlanRunner.cpp
        interval/PlanToJson.h
        interval/PlanToJson.cpp
)

