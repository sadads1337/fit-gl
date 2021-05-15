set(SRCS
        main.cpp
        Sphere.cpp
        Sphere.h
        Material.h
        Ray.h
        Light.h
        Plane.cpp
        Plane.h
        )

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(sayfudinova-task5 ${SRCS})

target_link_libraries(sayfudinova-task5
        PRIVATE
        Qt5::Widgets
        FGL::Base
        )