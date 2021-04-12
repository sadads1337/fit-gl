set(Task3_SRCS
        main.cpp

        MainWindow.cpp MainWindow.h
        GeometryEngine.cpp GeometryEngine.h
        Controller/InputController.cpp Controller/InputController.h

        shaders.qrc
        Shaders/phong_vshader.glsl
        Shaders/phong_fshader.glsl
        Shaders/gouraud_vshader.glsl
        Shaders/gouraud_fshader.glsl
        )

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(NikolaevTask3 ${Task3_SRCS})

target_link_libraries(NikolaevTask3
    PRIVATE
        Qt5::Widgets
)

