set(POPOVA_TASK3_SRCS
    main.cpp
    SquareWindow.cpp
    SquareWindow.hpp

    shaders.qrc
    Shaders/square.fs
    Shaders/square.vs
)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(PopovaTask3 ${POPOVA_TASK3_SRCS})

target_link_libraries(PopovaTask3
    PRIVATE
        Qt5::Widgets
        FGL::Base
)

