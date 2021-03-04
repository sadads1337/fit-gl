set(Task2_SRCS
    main.cpp
            cubemorphing.cpp
            cubemorphing.h
            cubemorphing.ui
            cubewidget.h
            GLCubeMeshGenerator.cpp
            GLCubeMeshGenerator.h
            GLCubeMeshRenderer.cpp
            GLCubeMeshRenderer.h
            GLFlatMeshGenerator.cpp
            GLFlatMeshGenerator.h
            GLMesh.cpp
            GLMesh.h
            GLMeshGenerator.cpp
            GLMeshGenerator.h
            GLMeshRenderer.cpp
            GLMeshRenderer.h
            GLVertex.h
            morphingwidget.cpp
            morphingwidget.h
            morphingwidget.ui
            
            shaders.qrc
            Shaders/vshader.vsh
            Shaders/fshader.fsh

)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(OpenGL REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS})

add_executable(DevyatovskayaTask2 ${Task2_SRCS})

target_link_libraries(DevyatovskayaTask2 PRIVATE
    Qt5::Widgets
    ${OPENGL_LIBRARIES})
