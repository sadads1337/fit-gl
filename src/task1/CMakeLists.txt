set(TASK-1_SRCS
        main.cpp
        CubeWindow.cpp
        CubeWindow.hpp

        shaders.qrc
        Shaders/square.fs
        Shaders/square.vs
        )

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(task-1 ${TASK-1_SRCS})

target_link_libraries(task-1
        PRIVATE
        Qt5::Widgets
        FGL::Base
        )

