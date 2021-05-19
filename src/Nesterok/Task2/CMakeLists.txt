set(Task2_SRCS
        main.cpp
        GLWidget.cpp
        GLWidget.hpp

        shaders.qrc
        Shaders/cube.fs
        Shaders/cube.vs
        WidgetUI.cpp WidgetUI.h)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(NesterokTask2 ${Task2_SRCS})

target_link_libraries(NesterokTask2
        PRIVATE
        Qt5::Widgets
        Base
        )