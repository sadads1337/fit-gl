find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(KononovTask2
        ${KONONOV_RESOURCES}
        shaders.qrc
        shaders/second.vert
        shaders/second.geom
        shaders/second.frag

        main.cpp
        Vertex.hpp
        SecondWindow.cpp
        SecondWindow.hpp
        SecondShader.cpp
        SecondShader.hpp
        SecondRenderable.cpp
        SecondRenderable.hpp)

target_link_libraries(KononovTask2
        PRIVATE Qt5::Widgets
        PUBLIC Kononov::Common)
