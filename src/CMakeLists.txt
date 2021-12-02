cmake_minimum_required(VERSION 3.21)


set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)

OPTION(BUILD_INTERVALL_APPLICATON "Build the Application" ON)

include(tests.cmake)
include(intervall.cmake)

if(${BUILD_INTERVALL_APPLICATON})
    qt_add_executable(appIntervalltimer
        main.cpp
    )

    qt_add_qml_module(appIntervalltimer
        URI Intervalltimer
        VERSION 1.0
        QML_FILES qml/main.qml
    )

    target_compile_definitions(appIntervalltimer
        PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
    target_link_libraries(appIntervalltimer
        PRIVATE Qt6::Quick)
endif()
