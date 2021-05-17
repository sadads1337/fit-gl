set(Task4_SRCS
        main.cpp
        MainWindow.cpp
        MainWindow.h
        GeometryEngine.cpp
        GeometryEngine.h
        Controller/InputController.cpp
        Controller/InputController.h

        shaders.qrc
        Shaders/phong_vshader.glsl
        Shaders/phong_fshader.glsl
        Shaders/gouraud_vshader.glsl
        Shaders/gouraud_fshader.glsl

        textures.qrc
        Textures/texture0.png
        Textures/texture1.png
        Textures/texture2.png
        )

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(NikolaevTask4 ${Task4_SRCS})

target_link_libraries(NikolaevTask4
        PRIVATE
        Qt5::Widgets
        )

