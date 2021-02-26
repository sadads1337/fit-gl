find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(ostapchenkotask1
        main.cpp
        SquareWindow.cpp
        SquareWindow.h

        shaders.qrc
        Shaders/square.fs
        Shaders/square.vs
        )

target_link_libraries(ostapchenkotask1
        PRIVATE
            Qt5::Widgets
            FGL::Base
        )