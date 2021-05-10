find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(ostapchenkotask5

        main.cpp Ray.h Sphere.cpp Sphere.h Plane.cpp Plane.h Hittable.h)

target_link_libraries(ostapchenkotask5
        PRIVATE
            Qt5::Widgets
            FGL::Base
        )