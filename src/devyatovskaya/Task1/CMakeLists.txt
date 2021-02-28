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

add_executable(DevyatovskayaTask1 ${Task1_SRCS})

target_link_libraries(DevyatovskayaTask1
    PRIVATE
        Qt5::Widgets
        FGL::Base
)
