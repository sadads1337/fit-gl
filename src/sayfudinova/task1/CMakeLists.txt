set(SRCS
        main.cpp
        CubeWindow.cpp
        CubeWindow.h

        shaders.qrc
        Shaders/triangle.fs
        Shaders/triangle.vs
        )

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(sayfudinova-task1 ${SRCS})

target_link_libraries(sayfudinova-task1
        PRIVATE
        Qt5::Widgets
        FGL::Base
        )