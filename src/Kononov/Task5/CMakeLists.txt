find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(KononovTask5
        main.cpp
        Types.hpp
        Colors.hpp
        Ground.cpp
        Ground.hpp
        Sphere.cpp
        Sphere.hpp
        Geometry.cpp
        Geometry.hpp
        Renderable.hpp
        Lightning.cpp
        Lightning.hpp)

target_link_libraries(KononovTask5
        PRIVATE Qt5::Widgets)
