find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(BazhenovTask1
        main.cpp
        MainWindow.hpp MainWindow.cpp)

target_link_libraries(BazhenovTask1
        PRIVATE
            Qt5::Widgets
            FGL::Base
)