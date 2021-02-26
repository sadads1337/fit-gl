cmake_minimum_required(VERSION 3.5)

project(Try LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Task1_SRCS
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

        shaders.qrc
        Shaders/vshader.vs
        Shaders/fshader.fs
)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(Task1 ${Task1_SRCS})

target_link_libraries(Task1
    PRIVATE
        Qt5::Widgets
        FGL::Base
)
