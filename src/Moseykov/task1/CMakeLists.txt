set(TASK1_SRCS
    main.cpp
    SquareWindow.cpp
    SquareWindow.hpp

    shaders.qrc
    Shaders/square.fs
    Shaders/square.vs
)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(task1 ${TASK1_SRCS})

target_link_libraries(task1
    PRIVATE
        Qt5::Widgets
        FGL::Base
)

