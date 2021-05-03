set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
add_executable(
        Task_5
        main.cpp
        Ray.h Sphere.cpp Sphere.h Material.h Light.h textures.qrc Plane.cpp Plane.h)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

target_link_libraries(Task_5 Qt5::Widgets)
