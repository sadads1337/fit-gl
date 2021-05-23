set(SRC
    main.cpp
    figure.cpp
    figure.hpp
    uiwindow.cpp
    uiwindow.h
    cube.cpp
    cube.hpp

    shaders.qrc
    Shaders/vshader.vs
    Shaders/fshader.fs
)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(EXE ${SRC})

target_link_libraries(EXE
    PRIVATE
        Qt5::Widgets
        FGL::Base
)
