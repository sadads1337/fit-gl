
find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(AntonovaTask4
        shaders.qrc
        Shaders/cube.fs
        Shaders/cube.vs

        texture.qrc

        main.cpp
        CubeWindow.cpp
        CubeWindow.hpp)

target_link_libraries(AntonovaTask4
        PRIVATE Qt5::Widgets
        PUBLIC FGL::Base)