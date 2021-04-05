cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(Task2 VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(Task2_SRSC
        main.cpp
        FPSCounter.cpp
        FPSCounter.h
        GLCamera.cpp
        GLCamera.h
        GLCameraMover.cpp
        GLCameraMover.h
        GLDirectedLight.cpp
        GLDirectedLight.h
        GLMaterial.cpp
        GLMaterial.h
        GLLightSource.cpp
        GLLightSource.h
        GLCubeMeshGenerator.cpp
        GLCubeMeshGenerator.h
        GLFlatMeshGenerator.cpp
        GLFlatMeshGenerator.h
        GLMesh.cpp
        GLMesh.h
        GLMeshGenerator.h
        GLMeshGenerator.cpp
        GLMeshRenderer.cpp
        GLMeshRenderer.h
        GLMeshRendererGenerator.h
        GLPointLight.cpp
        GLPointLight.h
        GLObject.cpp
        GLObject.h
        GLScene.cpp
        GLScene.h
        GLSceneRenderer.cpp
        GLSceneRenderer.h
        GLSimpleMeshRenderer.h
        GLSimpleMeshRenderer.cpp
        GLSimpleMeshRendererGenerator.cpp
        GLSimpleMeshRendererGenerator.h
        GLSphereMeshGenerator.cpp
        GLSphereMeshGenerator.h
        GLTransform.cpp
        GLTransform.h
        GLVertex.h
        LightingDialog.h
        LightingDialog.ui
        GLSpotLight.cpp
        GLSpotLight.h
        LigtingDialog.cpp
        MeshGeneratorCollecrion.h
        MorphingDialog.cpp
        MorphingDialog.h
        MorphingDialog.ui
        PhongLighting.ui
        PhongLightingWidget.cpp
        PhongLightingWidget.h
        PhongLighting.h
        PhongLighting.cpp
        PhongLighting.qrc
        PreparedScenes.cpp
        PreparedScenes.h
        RenderDialog.cpp
        RenderDialog.h
        RenderDialog.ui
        ShaderCollection.h
        ShaderData.cpp
        ShaderData.h

        shaders.qrc
        Shaders/f_morphing.glsl
        Shaders/v_morphing.glsl
        Shaders/Lighting/v_light_source.glsl
        Shaders/Lighting/f_light_source.glsl
        Shaders/Lighting/v_phong_lighting_wo_normal_mapping.glsl
        Shaders/Lighting/f_phong_lighting_wo_normal_mapping.glsl
        Shaders/Lighting/v_phong_lighting_normal_mapping.glsl
        Shaders/Lighting/f_phong_lighting_normal_mapping.glsl
        Shaders/Lighting/v_guro_lighting_wo_normal_mapping.glsl
        Shaders/Lighting/f_guro_lighting_wo_normal_mapping.glsl
)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(OpenGL REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS})

qt5_wrap_ui(UI_HEADERS PhongLighting.ui RenderDialog.ui MorphingDialog.ui)

add_executable(Task2 ${Task2_SRSC}  ${UI_HEADERS})

target_link_libraries(Task2 PRIVATE
    Qt5::Widgets
    ${OPENGL_LIBRARIES})
    
