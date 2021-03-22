add_executable(
        Task_3
        main.cpp
        Widget.cpp
        Widget.h
        Object3D.cpp
        Object3D.h
        Window.cpp
        Window.h
        MainWindow.cpp
        MainWindow.h
        shaders.qrc
        textures.qrc
        shaders/gouraud_fshader.fsh
        shaders/gouraud_vshader.vsh
        shaders/phong_fshader.fsh
        shaders/phong_vshader.vsh
        shaders/blinn-phong_fshader.fsh
        shaders/blinn-phong_vshader.vsh
)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

target_link_libraries(Task_3 Qt5::Widgets)
