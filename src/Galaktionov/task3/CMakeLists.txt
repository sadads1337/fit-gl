set(SRCS
        main.cpp
        CubeWindow.cpp
        CubeWindow.h
        shaders.qrc
        f_shader.fs
        v_shader.vs
        )

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(Galaktionov-task3 ${SRCS})

target_link_libraries(Galaktionov-task3
    PRIVATE
    Qt5::Widgets
    FGL::Base
    )
