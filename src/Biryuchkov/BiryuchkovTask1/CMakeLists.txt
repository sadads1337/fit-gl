set(BiryuchkovTask1_SRCS

        shaders.qrc
        Shaders/square.fs
        Shaders/square.vs
        CubeWindow.cpp CubeWindow.hpp main.cpp)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(BiryuchkovTask1 ${BiryuchkovTask1_SRCS})

target_link_libraries(BiryuchkovTask1
        PRIVATE
        Qt5::Widgets
        FGL::Base
        )