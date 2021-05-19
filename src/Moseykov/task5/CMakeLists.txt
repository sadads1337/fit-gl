find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(MoseykovTask5
        main.cpp
        Ray.h
        Sphere.cpp
        Sphere.h
        Floor.cpp
        Floor.h
        Hittable.h)

target_link_libraries(MoseykovTask5
        PRIVATE
        Qt5::Widgets
        FGL::Base
        )