find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_subdirectory(export)

add_executable(KononovTask1
        ${KONONOV_RESOURCES}
        shaders.qrc
        shaders/first.fs
        shaders/first.vs

        main.cpp
        MainWindow.cpp
        MainWindow.hpp)

target_link_libraries(KononovTask1
        PRIVATE Qt5::Widgets
        PUBLIC Kononov::Common
        PRIVATE Kononov::Task1::export)
