cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 20)

find_package(Qt6 COMPONENTS Quick Qml Sql Core REQUIRED)

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
        qml/LoadPlanView.qml
        qml/PlanView.qml
        qml/PlanEditorView.qml
        qml/PlanRunningView.qml
        qml/StorePlanView.qml
        qml/ProgressView.qml
    SOURCES
        intervaltimer/DatabaseProvider.h
        intervaltimer/DatabaseProvider.cpp
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
        intervaltimer/PlanStorageModel.h
        intervaltimer/PlanStorageModel.cpp
        intervaltimer/PlanToJson.h
        intervaltimer/PlanToJson.cpp
        intervaltimer/Timer.h
        intervaltimer/Timer.cpp
        intervaltimer/TimerBase.h
        intervaltimer/TimerBase.cpp
)

target_link_libraries(Intervaltimer PUBLIC
    PUBLIC Qt6::Quick
    PUBLIC Qt6::Qml
    PUBLIC Qt6::Sql
    PUBLIC Qt6::Core
    )
