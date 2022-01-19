cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 20)

find_package(Qt6 6.2 COMPONENTS Quick  REQUIRED)

qt_add_library(Intervaltimer STATIC)

target_include_directories(Intervaltimer PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/intervaltimer>
)

qt_add_qml_module(Intervaltimer
    URI Intervaltimer
    VERSION 1.0
    PLUGIN_TARGET IntervaltimerPlugin
    QML_FILES
        qml/IntervalView.qml
        qml/PlanView.qml
        qml/PlanEditorView.qml
        qml/PlanRunningView.qml
    SOURCES
        intervaltimer/Interval.cpp
        intervaltimer/Interval.h
        intervaltimer/IntervalFromJson.h
        intervaltimer/IntervalFromJson.cpp
        intervaltimer/IntervalToJson.h
        intervaltimer/IntervalToJson.cpp
        intervaltimer/Plan.cpp
        intervaltimer/Plan.h
        intervaltimer/PlanIterator.h
        intervaltimer/PlanIterator.cpp
        intervaltimer/PlanModel.cpp
        intervaltimer/PlanModel.h
        intervaltimer/PlanFromJson.h
        intervaltimer/PlanFromJson.cpp
        intervaltimer/PlanRunner.h
        intervaltimer/PlanRunner.cpp
        intervaltimer/PlanToJson.h
        intervaltimer/PlanToJson.cpp
        intervaltimer/TimerBase.h
        intervaltimer/TimerBase.cpp
)

