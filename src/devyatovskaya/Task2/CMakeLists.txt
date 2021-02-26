cmake_minimum_required(VERSION 3.5)

project(Task2 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(Task2_SRSC
        main.cpp
        Geometry.h
        GeometryPainter.h
        Geometry.cpp
        CubicGeometry.h
        cubepainter.cpp
        cubewindow.cpp
        cubewindow.h
        cubepainter.h
        cubegeometry.cpp
        cubegeometry.h
        cubeedges.cpp
        cubeedges.h
        cubewidget.h
        cubewidget.cpp

        shaders.qrc
        Shaders/vshader.vs
        Shaders/fshader.fs
)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(Task2 ${Task2_SRSC})

target_link_libraries(Task2
    PRIVATE
        Qt5::Widgets
        GL
)
