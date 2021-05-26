set(SRCS
    main.cpp
    CubeWindow.cpp
    CubeWindow.h
    shaders.qrc
    textures.qrc
    f_shader.fsh
    v_shader.vsh
    )

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(Galaktionov-task2 ${SRCS})

target_link_libraries(Galaktionov-task2
    PRIVATE
    Qt5::Widgets
    FGL::Base
    )
