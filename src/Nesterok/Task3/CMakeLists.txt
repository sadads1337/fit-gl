set(Task3_SRCS
        main.cpp
        GLWidget.cpp
        GLWidget.hpp

        shaders.qrc
        Shaders/cube.fs
        Shaders/cube.vs
        WidgetUI.cpp WidgetUI.h)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(NesterokTask3 ${Task3_SRCS})

target_link_libraries(NesterokTask3
        PRIVATE
        Qt5::Widgets
        )