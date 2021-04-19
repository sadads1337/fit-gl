
find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(AntonovaTask2
        shaders.qrc
        Shaders/cube.fs
        Shaders/cube.vs

        main.cpp
        CubeWindow.cpp
        CubeWindow.hpp)

target_link_libraries(AntonovaTask2
        PRIVATE Qt5::Widgets
        PUBLIC FGL::Base)