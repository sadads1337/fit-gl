add_executable(BiryuchkovTask5v2
        main.cpp
        Surface.cpp
        Surface.h
        Hit_light.h
        Hit_ray.h
        Material.h
        Sphere.cpp Sphere.h)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

target_link_libraries(BiryuchkovTask5v2 Qt5::Widgets)