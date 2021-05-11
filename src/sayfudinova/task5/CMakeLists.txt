set(SRCS
        main.cpp
        CubeWindow.cpp
        CubeWindow.h

        shaders.qrc
        Shaders/quad.fs
        Shaders/quad.vs
        )

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(sayfudinova-task5 ${SRCS})

target_link_libraries(sayfudinova-task5
        PRIVATE
        Qt5::Widgets
        FGL::Base
        )