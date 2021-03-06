set(LESSON1_SRCS
    main.cpp
    CubeWindow.cpp
    CubeWindow.hpp

    shaders.qrc
    Shaders/cube.fs
    Shaders/cube.vs
)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(BondarchukTask1 ${LESSON1_SRCS})

target_link_libraries(BondarchukTask1
    PRIVATE
        Qt5::Widgets
        FGL::Base
)

