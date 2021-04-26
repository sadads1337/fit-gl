find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(ostapchenkotask4
        main.cpp
        MainWindow.cpp
        MainWindow.h

        shaders.qrc
        Shaders/fragment_shader.fs
        Shaders/vertex_shader.vs

        textures.qrc

        )

target_link_libraries(ostapchenkotask4
        PRIVATE
            Qt5::Widgets
            FGL::Base
        )