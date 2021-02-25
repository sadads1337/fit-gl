find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(KononovTask2
        ${KONONOV_RESOURCES}
        shaders.qrc
        shaders/second.fs
        shaders/second.vs

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
