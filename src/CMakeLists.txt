cmake_minimum_required(VERSION 3.21)

find_package(Qt6 COMPONENTS Quick Qml Sql Core QuickControls2 Test REQUIRED)

OPTION(BUILD_INTERVAL_APPLICATON "Build the Application" ON)

add_subdirectory(Intervaltimer)

include(tests.cmake)

if(${BUILD_INTERVAL_APPLICATON})
    qt_add_executable(IntervaltimerApplication
        main.cpp
    )
    qt_add_qml_module(IntervaltimerApplication
        URI IntervalApplication
        VERSION 1.0
        QML_FILES 
            mainDesctop.qml
            mainAndroid.qml
        IMPORT_PATH "${QML_IMPORT_PATH}/src"
        RESOURCES
            ../ressources/image/closed.png
            ../ressources/image/expanded.png
            ../ressources/image/menu.png
    )

    target_compile_definitions(IntervaltimerApplication
        PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
    target_link_libraries(IntervaltimerApplication
        PRIVATE Qt6::Quick
        PRIVATE Qt6::QuickControls2
        PRIVATE Intervaltimer
        )
endif()
