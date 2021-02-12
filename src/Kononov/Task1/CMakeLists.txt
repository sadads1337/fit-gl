find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(KononovTask1
        shaders.qrc
        shaders/first.fs
        shaders/first.vs

        textures.qrc
        textures/dice-diffuse.png
        textures/skull-diffuse.jpg

        models.qrc
        models/skull.vbo-ibo

        main.cpp
        MainWindow.cpp
        MainWindow.hpp
        ShaderProgram.cpp
        ShaderProgram.hpp
        FirstShader.cpp
        FirstShader.hpp
        FirstRenderable.cpp
        FirstRenderable.hpp
        FirstSceneObject.cpp
        FirstSceneObject.hpp)

target_link_libraries(KononovTask1
        PRIVATE Qt5::Widgets
        PUBLIC Kononov::Common)
