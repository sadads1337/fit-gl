find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(BazhenovTask4
    main.cpp

    MainWindow.hpp
    MainWindow.cpp

    InputController/InputController.hpp
    InputController/InputController.cpp

    shaders.qrc
    Shaders/phong_vertex.glsl
    Shaders/phong_fragment.glsl
    Shaders/gouraud_vertex.glsl
    Shaders/gouraud_fragment.glsl

    textures.qrc
    Textures/glyphs.jpg
    Textures/glyphs-normal.jpg
)

target_link_libraries(BazhenovTask4
    PRIVATE
        Qt5::Widgets
        Base
)