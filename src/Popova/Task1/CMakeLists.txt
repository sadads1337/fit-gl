set(POPOVA_TASK1_SRCS
    main.cpp
    SquareWindow.cpp
    SquareWindow.hpp

    shaders.qrc
    Shaders/square.fs
    Shaders/square.vs
)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(PopovaTask1 ${POPOVA_TASK1_SRCS})

target_link_libraries(PopovaTask1
    PRIVATE
        Qt5::Widgets
        FGL::Base
)

