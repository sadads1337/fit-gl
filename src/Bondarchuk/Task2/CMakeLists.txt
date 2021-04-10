set(SRCS
    main.cpp
    CubeWindow.cpp
    CubeWindow.hpp

    shaders.qrc
    Shaders/cube.fs
    Shaders/cube.vs
)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(BondarchukTask2 ${SRCS})

target_link_libraries(BondarchukTask2
    PRIVATE
        Qt5::Widgets
        FGL::Base
)

