cmake_minimum_required(VERSION 3.21)


set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)

OPTION(BUILD_INTERVAL_APPLICATON "Build the Application" ON)

include(tests.cmake)
include(interval.cmake)

if(${BUILD_INTERVAL_APPLICATON})
    qt_add_executable(appIntervaltimer
        main.cpp
    )

    qt_add_qml_module(appIntervaltimer
        URI Intervaltimer
        VERSION 1.0
        QML_FILES qml/main.qml
    )

    target_compile_definitions(appIntervaltimer
        PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
    target_link_libraries(appIntervaltimer
        PRIVATE Qt6::Quick intervaltimer)
endif()
