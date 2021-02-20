cmake_minimum_required(VERSION 3.5)

project(Task1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mymainwindow.cpp
        mymainwindow.h
        plainobject3d.cpp
        plainobject3d.h
        CubeObject.h
        cubeedges.cpp
        cubeedges.h
        cube.cpp
        cube.h
        cubewindow.cpp
        cubewindow.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 5)
        add_executable(Task1
            ${PROJECT_SOURCES}
        )
endif()

target_link_libraries(Task1 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
