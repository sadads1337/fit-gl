set(Task1_SRCS
        main.cpp
        QuadWindow.cpp
        QuadWindow.hpp

        shaders.qrc
        Shaders/triangle.fs
        Shaders/triangle.vs
        )

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(NesterokTask1 ${Task1_SRCS})

target_link_libraries(NesterokTask1
        PRIVATE
        Qt5::Widgets
        Base
        )