find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(MoseykovTask3
        main.cpp
        SquareWindow.hpp
        SquareWindow.cpp
        Shaders/guro.fs
        Shaders/guro.vs
        Shaders/phong.fs
        Shaders/phong.vs
        shaders.qrc
        MyWidget.h
        MyWidget.cpp)

target_link_libraries(MoseykovTask3
    PRIVATE
        Qt5::Widgets
        FGL::Base
)

