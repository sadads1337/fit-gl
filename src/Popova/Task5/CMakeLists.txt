set(POPOVA_TASK5_SRCS
    main.cpp
    Material.hpp
    Plane.hpp
    Plane.cpp
    Types.hpp
    Sphere.hpp
    Sphere.cpp
)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(PopovaTask5 ${POPOVA_TASK5_SRCS})

target_link_libraries(PopovaTask5
    PRIVATE
        Qt5::Widgets
        FGL::Base
)

