add_executable(ShabalovTask5
        main.cpp
        Ray.h
        Sphere.cpp
        Sphere.h
        Material.h
        Light.h
        textures.qrc
        Plane.cpp
        Plane.h
)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

target_link_libraries(ShabalovTask5 Qt5::Widgets)
