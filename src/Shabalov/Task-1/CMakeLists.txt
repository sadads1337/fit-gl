set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(Task_1 main.cpp Widget.cpp Widget.h Object3D.cpp Object3D.h Window.cpp Window.h MainWindow.cpp MainWindow.h shaders.qrc textures.qrc shaders/fshader.fsh shaders/vshader.vsh)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

target_link_libraries(Task_1 Qt5::Widgets)
