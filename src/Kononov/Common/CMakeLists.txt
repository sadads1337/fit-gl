find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_library(KononovCommon
        DirectionInputController.cpp
        DirectionInputController.hpp
        MotionInputController.cpp
        MotionInputController.hpp
        PositionedObject.cpp
        PositionedObject.hpp
        SceneObject.cpp
        SceneObject.hpp
        Renderable.hpp
        Resources.cpp
        Resources.hpp
        Camera.cpp
        Camera.hpp
        GLUtil.cpp
        GLUtil.hpp
        Vertex.hpp
        Shader.hpp
        Mesh.hpp)

target_include_directories(KononovCommon
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(KononovCommon
        PRIVATE Qt5::Widgets
        PUBLIC FGL::Base)

add_library(Kononov::Common ALIAS KononovCommon)
