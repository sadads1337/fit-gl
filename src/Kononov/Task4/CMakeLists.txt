find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(KononovTask4
        ${KONONOV_RESOURCES}
        shaders.qrc
        shaders/fourth.vert
        shaders/fourth.frag

        main.cpp
        FourthWindow.cpp
        FourthWindow.hpp
        )

target_link_libraries(KononovTask4
        PRIVATE Qt5::Widgets
        PUBLIC Kononov::Common
        PUBLIC Kononov::Task1::export)
