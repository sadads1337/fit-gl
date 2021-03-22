find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(KononovTask2
        ${KONONOV_RESOURCES}
        shaders.qrc
        shaders/second.vert
        shaders/second.geom
        shaders/second.frag
        shaders/second-cube.geom
        shaders/second-cube.tese
        shaders/second-cube.tesc
        shaders/second-cube.vert

        main.cpp
        SecondWindow.cpp
        SecondWindow.hpp
        SecondShader.hpp
        TesselatedRenderable.cpp
        TesselatedRenderable.hpp)

target_link_libraries(KononovTask2
        PRIVATE Qt5::Widgets
        PUBLIC Kononov::Common
        PUBLIC Kononov::Task1::export)
