cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 20)

find_package(Qt6 COMPONENTS Quick Qml Sql Core REQUIRED)

qt_add_library(Intervaltimer STATIC)
qt_add_library(IntervaltimerCpp STATIC)
qt_add_library(IntervaltimerDesctop STATIC)
qt_add_library(IntervaltimerAndroid STATIC)

target_include_directories(IntervaltimerCpp PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/intervaltimer>
)

qt_add_qml_module(IntervaltimerCpp
    URI Intervaltimer
    VERSION 1.0
    PLUGIN_TARGET IntervaltimerCppPlugin
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
    OUTPUT_DIRECTORY IntervaltimerCpp
)

target_link_libraries(IntervaltimerCpp PUBLIC
    PUBLIC Qt6::Quick
    PUBLIC Qt6::Qml
    PUBLIC Qt6::Sql
    PUBLIC Qt6::Core
)


target_include_directories(IntervaltimerDesctop PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/intervaltimer>
)

qt_add_qml_module(IntervaltimerDesctop
    URI Intervaltimer.Desctop
    VERSION 1.0
    PLUGIN_TARGET IntervaltimerDesctopPlugin
    QML_FILES
        qml/desctop/IntervalView.qml
        qml/desctop/LoadPlanView.qml
        qml/desctop/PlanView.qml
        qml/desctop/PlanEditorView.qml
        qml/desctop/PlanRunningView.qml
        qml/desctop/StorePlanView.qml
        qml/desctop/ProgressView.qml
    OUTPUT_DIRECTORY Intervaltimer
)

target_link_libraries(IntervaltimerDesctop PUBLIC
    PUBLIC Qt6::Quick
    PUBLIC Qt6::Qml
    PUBLIC Qt6::Sql
    PUBLIC Qt6::Core
    PRIVATE IntervaltimerCppPlugin
    PRIVATE IntervaltimerCpp
    )

target_include_directories(IntervaltimerAndroid PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/intervaltimer>
)


qt_add_qml_module(IntervaltimerAndroid
    URI Intervaltimer.Android
    VERSION 1.0
    PLUGIN_TARGET IntervaltimerAndroidPlugin
    QML_FILES
        qml/android/DurationControl.qml
        qml/android/IntervalView.qml
        qml/android/LoadPlanView.qml
        qml/android/PlanView.qml
        qml/android/PlanEditorView.qml
        qml/android/PlanRunningView.qml
        qml/android/StorePlanView.qml
        qml/android/ProgressView.qml
        qml/android/DurationTumbler.qml
)

target_link_libraries(IntervaltimerAndroid PUBLIC
    PUBLIC Qt6::Quick
    PUBLIC Qt6::Qml
    PUBLIC Qt6::Sql
    PUBLIC Qt6::Core
    PRIVATE IntervaltimerCppPlugin
    PRIVATE IntervaltimerCpp
)

target_link_libraries(Intervaltimer PUBLIC
    PUBLIC IntervaltimerCppPlugin
    PUBLIC IntervaltimerCpp
    PUBLIC IntervaltimerAndroidPlugin
    PUBLIC IntervaltimerAndroid
    PUBLIC IntervaltimerDesctopPlugin
    PUBLIC IntervaltimerDesctop
)

