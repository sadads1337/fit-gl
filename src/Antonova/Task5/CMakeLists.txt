find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(AntonovaTask5
        Ray.h
        Hittable.h
        Hit.h
        Sphere.cpp
        Sphere.h Plane.cpp Plane.h Tracer.cpp Tracer.h main.cpp)

target_link_libraries(AntonovaTask5
        PRIVATE Qt5::Widgets
        PUBLIC FGL::Base)