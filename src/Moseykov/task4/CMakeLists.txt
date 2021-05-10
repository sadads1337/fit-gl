find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(MoseykovTask4
        main.cpp
        SquareWindow.hpp
        SquareWindow.cpp
        Shaders/square.fs
        Shaders/square.vs
        shaders.qrc
        textures.qrc)

target_link_libraries(MoseykovTask4
    PRIVATE
        Qt5::Widgets
        FGL::Base
)

