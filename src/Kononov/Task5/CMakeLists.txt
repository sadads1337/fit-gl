find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(KononovTask5 main.cpp Geometry.cpp Geometry.hpp Renderable.hpp Ground.cpp Ground.hpp Types.hpp Sphere.cpp Sphere.hpp Lightning.cpp Lightning.hpp Colors.hpp)

target_link_libraries(KononovTask5
        PRIVATE Qt5::Widgets)
