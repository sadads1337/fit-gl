set(LESSON1_SRCS
    main.cpp
    CubeWindow.cpp
    CubeWindow.hpp

    shaders.qrc
    Shaders/cube.fs
    Shaders/cube.vs

    textures.qrc
    textures/brickwall.jpg
    textures/brickwall_normal.jpg
)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(BondarchukTask4 ${LESSON1_SRCS})

target_link_libraries(BondarchukTask4
    PRIVATE
        Qt5::Widgets
        FGL::Base
)

