find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(KononovTask1
        shaders.qrc
        shaders/first.fs
        shaders/first.vs

        textures.qrc
        textures/dice-diffuse.png

        main.cpp
        MainWindow.cpp
        MainWindow.hpp
        FirstShader.cpp
        FirstShader.hpp)

target_link_libraries(KononovTask1
        PRIVATE Qt5::Widgets
        PUBLIC Kononov::Common)
