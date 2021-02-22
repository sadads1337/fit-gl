find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(KononovTask2
        shaders.qrc
        shaders/second.fs
        shaders/second.vs

        textures.qrc
        textures/dice-diffuse.png

        models.qrc

        main.cpp
        Vertex.hpp
        MainWindow.cpp
        MainWindow.hpp
        SecondShader.cpp
        SecondShader.hpp
        SecondRenderable.cpp
        SecondRenderable.hpp)

target_link_libraries(KononovTask2
        PRIVATE Qt5::Widgets
        PUBLIC Kononov::Common)
