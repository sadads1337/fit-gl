cmake_minimum_required(VERSION 3.5)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.hpp
    mainwindow.ui
    vshader.glsl
    fshader.glsl
    shaders.qrc
       
    globject.hpp
    rectflatgridsurface.cpp
    rectflatgridsurface.hpp
    cameraview.cpp
    cameraview.hpp
    cube.cpp
    cube.hpp
    cubewidget.cpp
    cubewidget.hpp
    mainwindow.ui
)

find_package(Qt5 COMPONENTS Gui Widgets REQUIRED)

add_executable(BiryuchkovTask2 ${PROJECT_SOURCES})

target_link_libraries(BiryuchkovTask2 PRIVATE Qt5::Gui Qt5::Widgets)
