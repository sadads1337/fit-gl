add_executable(AntonovaTask2
    shaders.qrc
    Shaders/cube.fs
    Shaders/cube.vs

    main.cpp
    CubeWindow.cpp
    CubeWindow.hpp
)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

target_link_libraries(AntonovaTask2
    PRIVATE 
        Qt5::Widgets
        FGL::Base
)
