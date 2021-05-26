set(SRC2
    main.cpp
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

add_executable(VoitovTask2 ${SRC2})

target_link_libraries(VoitovTask2
    PRIVATE
        Qt5::Widgets
        FGL::Base
)
