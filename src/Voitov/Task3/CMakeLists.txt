set(SRC3
    main.cpp
    figure.cpp
    figure.hpp
    uiwindow.cpp
    uiwindow.h
    cube.cpp
    cube.hpp
    figureinformation.h
    figureinformation.cpp

    shaders.qrc
)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(VoitovTask3 ${SRC3})

target_link_libraries(VoitovTask3
    PRIVATE
        Qt5::Widgets
        FGL::Base
)
