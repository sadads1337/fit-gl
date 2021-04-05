find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(KononovTask3
        ${KONONOV_RESOURCES}
        shaders.qrc
        shaders/third-common.glsl
        shaders/third-gouraud.vert
        shaders/third-gouraud.frag
        shaders/third-phong.vert
        shaders/third-phong.frag

        main.cpp
        ThirdWindow.cpp
        ThirdWindow.hpp
        )

target_link_libraries(KononovTask3
        PRIVATE Qt5::Widgets
        PUBLIC Kononov::Common
        PUBLIC Kononov::Task1::export)
