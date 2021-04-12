find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(MoseykovTask2
        main.cpp
        SquareWindow.hpp
        SquareWindow.cpp
        Shaders/square.fs
        Shaders/square.vs
        shaders.qrc
        MyWidget.h
        MyWidget.cpp)

target_link_libraries(MoseykovTask2
    PRIVATE
        Qt5::Widgets
        FGL::Base
)

