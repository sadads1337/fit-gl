set(Task1_SRCS
        main.cpp

        MainWindow.cpp MainWindow.h
        geometryengine.cpp geometryengine.h
        Controller/InputController.cpp Controller/InputController.h

        shaders.qrc
        Shaders/vshader.glsl
        Shaders/fshader.glsl

        textures.qrc
        cube.png
        cube.pro)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(Task1 ${Task1_SRCS})

target_link_libraries(Task1
    PRIVATE
        Qt5::Widgets
)

