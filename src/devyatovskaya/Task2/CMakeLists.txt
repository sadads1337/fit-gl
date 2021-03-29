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
        ui_MorphingDialog.h
        ui_PhongLighting.h
        ui_RenderDialog.h

        shaders.qrc
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
    
