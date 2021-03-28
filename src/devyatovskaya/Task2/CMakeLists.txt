cmake_minimum_required(VERSION 3.5)

project(Task2 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Task2_SRSC
        main.cpp
        GLCamera.cpp
        GLCamera.h
        GLCameraMover.cpp
        GLCameraMover.h
        GLCubeMeshGenerator.cpp
        GLCubeMeshGenerator.h
        GLFlatMeshGenerator.cpp
        GLFlatMeshGenerator.h
        GLMesh.cpp
        GLMesh.h
        GLMeshGenerator.h
        GLMeshRenderer.cpp
        GLMeshRenderer.h
        GLMeshRendererGenerator.h
        GLObject.cpp
        GLObject.h
        GLScene.cpp
        GLScene.h
        GLSceneRenderer.cpp
        GLSceneRenderer.h
        GLSimpleMeshRenderer.h
        GLSimpleMeshRendererGenerator.cpp
        GLSimpleMeshRendererGenerator.h
        GLSphereMeshGenerator.cpp
        GLSphereMeshGenerator.h
        GLTransform.cpp
        GLTransform.h
        GLVertex.h
        MeshGeneratorCollecrion.h
        MorphingDialog.cpp
        MorphingDialog.h
        MorphingDialog.ui
        PhongLighting.ui
        PhongLightingWidget.cpp
        PhongLightingWidget.h
        PhongLighting.h
        PhongLighting.qrc
        PreparedScenes.cpp
        PreparedScenes.h
        RenderDialog.cpp
        RenderDialog.h
        RenderDialog.ui
        ShaderCollection.h
        ShaderData.cpp
        ShaderData.h
        ui_MorphingDialog.h
        ui_PhongLighting.h
        ui_RenderDialog.h

        shader.qrc
        Shaders/f_morphing.glsl
        Shaders/v_morphing.glsl
)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(OpenGL REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS})

qt5_wrap_ui(UI_HEADERS PhongLighting.ui RenderDialog.ui MorphingDialog.ui)

add_executable(Task2 ${Task2_SRSC}  ${UI_HEADERS})

target_link_libraries(Task2 PRIVATE
    Qt5::Widgets
    ${OPENGL_LIBRARIES})
