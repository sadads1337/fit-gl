find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(BazhenovTask5
        main.cpp

        Geometry/Geometry.cpp
        Geometry/Geometry.hpp

        Lighting/Ray.hpp
        Lighting/Colors.hpp

        Lighting/Light.cpp
        Lighting/Light.hpp

        Renderable/Renderable.hpp
        Renderable/Plane.cpp
        Renderable/Plane.hpp

        Renderable/Sphere.cpp
        Renderable/Sphere.hpp)

target_link_libraries(BazhenovTask5
        PRIVATE
        Qt5::Widgets
        Base
        )
