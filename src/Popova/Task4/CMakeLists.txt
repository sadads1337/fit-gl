set(POPOVA_TASK4_SRCS
        main.cpp
        SquareWindow.cpp
        SquareWindow.hpp

        shaders.qrc
        Shaders/square.fs
        Shaders/square.vs

        textures.qrc
        texture/normalmap.jpg
        texture/texture2.jpg
        )

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(PopovaTask4 ${POPOVA_TASK4_SRCS})

target_link_libraries(PopovaTask4
        PRIVATE
        Qt5::Widgets
        FGL::Base
        )

