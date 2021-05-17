find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(ostapchenkotask3
        main.cpp
        MainWindow.cpp
        MainWindow.h

        shaders.qrc
        Shaders/fragment_shader.fs
        Shaders/vertex_shader.vs
        CommonWidget.cpp
        CommonWidget.h)

target_link_libraries(ostapchenkotask3
        PRIVATE
        Qt5::Widgets
        FGL::Base
        )