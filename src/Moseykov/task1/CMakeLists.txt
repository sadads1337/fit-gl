find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(MoseykovTask1
        main.cpp
        SquareWindow.hpp
        SquareWindow.cpp
        Shaders/square.fs
        Shaders/square.vs
        shaders.qrc)

target_link_libraries(MoseykovTask1
    PRIVATE
        Qt5::Widgets
        FGL::Base
)

