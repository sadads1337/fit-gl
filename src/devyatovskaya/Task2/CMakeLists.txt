set(Task2_SRCS
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

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(OpenGL REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS})

add_executable(DevyatovskayaTask2 ${Task2_SRCS})

target_link_libraries(DevyatovskayaTask2 PRIVATE
    Qt5::Widgets
    ${OPENGL_LIBRARIES})
