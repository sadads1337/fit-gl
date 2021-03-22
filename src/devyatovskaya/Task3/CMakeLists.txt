set(Task3_SRCS
        main.cpp
        PhongLighting.cpp
        PhongLighting.h
        PhongLighting.ui
        FPSCounter.h
        GLCamera.h
        GLCameraMover.h
        GLLightSource.h
        GLMaterial.h
        GLMesh.h
        GLMeshGenerator.h
        GLMeshRenderer.h
        GLMeshRendererGenerator.h
        GLObject.h
        GLPointLight.h
        GLScene.h
        GLSceneRenderer.h
        GLSimpleMeshRenderer.h
        GLSimpleMeshRendererGenerator.h
        GLSphereMeshGenerator.h
        GLSpotLight.h
        GLTexture.h
        GLTextureLoader.h
        GLTransform.h
        GLVertex.h
        LightingDialog.h
        MeshGeneratorCollecrion.h
        PreparedScenes.h
        RenderDialog.h
        ShaderCollection.h
        ShaderData.h
        FPSCounter.cpp
        GLCamera.cpp
        GLCameraMover.cpp
        GLCubeMeshGenerator.cpp
        GLFlatMeshGenerator.cpp
        GLMesh.cpp
        GLMeshGenerator.cpp
        GLMeshRenderer.cpp
        GLScene.cpp
        GLSceneRenderer.cpp
        GLSimpleMeshRenderer.cpp
        GLSimpleMeshRendererGenerator.cpp
        GLSphereMeshGenerator.cpp
        GLTransform.cpp
        LigtingDialog.cpp
        PhongLightingWidget.cpp
        PreparedScenes.cpp
        RenderDialog.cpp
        ShaderData.cpp
        LightingDialog.ui
        RenderDialog.ui

        shaders.qrc
        Shaders/f_cube_morphing.glsl
        Shaders/v_cube_morphing.glsl
        Shaders/Lighting/f_guro_lighting.glsl
        Shaders/Lighting/v_guro_lighting.glsl
        Shaders/Lighting/f_phong_lighting.glsl
        Shaders/Lighting/v_phong_lighting.glsl
        Shaders/Lighting/f_light_source.glsl
        Shaders/Lighting/v_light_source.glsl

        Textures/Wow2.jpg
        Textures/Wow1.jpg
        Textures/Wow3.jpg


)
find_package( Qt5 COMPONENTS Widgets REQUIRED)
find_package(OpenGL REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS})
qt5_wrap_ui(UI_HEADERS PhongLighting.ui LightingDialog.ui RenderDialog.ui)

add_executable(DevyatovskayaTask3 ${Task3_SRCS} ${UI_HEADERS})

target_link_libraries(DevyatovskayaTask3 PRIVATE
    Qt5::Widgets
    ${OPENGL_LIBRARIES})
