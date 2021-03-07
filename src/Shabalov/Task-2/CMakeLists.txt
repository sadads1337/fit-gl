add_executable(Task_2
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
        shaders/fshader.fsh
        shaders/vshader.vsh)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

target_link_libraries(ShabalovTask1 Qt5::Widgets)
