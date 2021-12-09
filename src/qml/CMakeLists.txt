cmake_minimum_required(VERSION 3.21)

find_package(Qt6 6.2 COMPONENTS Quick  REQUIRED)

qt_add_library(IntervalTimerQML STATIC)

qt_add_qml_module(IntervalTimerQML
    URI Intervaltimergui
    VERSION 1.0
    QML_FILES main.qml Interval.qml Plan.qml
    OUTPUT_DIRECTORY Intervaltimergui
)

