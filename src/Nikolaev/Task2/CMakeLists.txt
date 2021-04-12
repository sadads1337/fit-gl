set(Task2_SRCS
        main.cpp

        MainWindow.cpp MainWindow.h
        GeometryEngine.cpp GeometryEngine.h
        Controller/InputController.cpp Controller/InputController.h

        shaders.qrc
        Shaders/vshader.glsl
        Shaders/fshader.glsl
        )

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(NikolaevTask2 ${Task2_SRCS})

target_link_libraries(NikolaevTask2
    PRIVATE
        Qt5::Widgets
)

