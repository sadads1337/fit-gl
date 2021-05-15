find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(BazhenovTask3
    main.cpp

    MainWindow.hpp
    MainWindow.cpp

    InputController/InputController.hpp
    InputController/InputController.cpp

    shaders.qrc
    Shaders/vertex.glsl
    Shaders/fragment.glsl
)

target_link_libraries(BazhenovTask3
    PRIVATE
        Qt5::Widgets
        Base
)