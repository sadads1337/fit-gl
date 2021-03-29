set(POPOVA_TASK2_SRCS
        main.cpp
        SquareWindow.cpp
        SquareWindow.hpp

        shaders.qrc
        Shaders/square.fs
        Shaders/square.vs
        )

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(PopovaTask2 ${POPOVA_TASK2_SRCS})

target_link_libraries(PopovaTask2
        PRIVATE
        Qt5::Widgets
        FGL::Base
        )

