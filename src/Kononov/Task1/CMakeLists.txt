find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(KononovTask1
        ${KONONOV_RESOURCES}
        shaders.qrc
        shaders/first.fs
        shaders/first.vs

        main.cpp
        Vertex.hpp
        MainWindow.cpp
        MainWindow.hpp
        FirstShader.cpp
        FirstShader.hpp
        FirstRenderable.cpp
        FirstRenderable.hpp)

target_link_libraries(KononovTask1
        PRIVATE Qt5::Widgets
        PUBLIC Kononov::Common)
