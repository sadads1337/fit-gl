set(SRC_LIST
        cameraview.cpp
        cameraview.hpp
        dialog.cpp
        dialog.hpp
        dialog.ui
        direcltylight.cpp
        direcltylight.hpp
        GuroSceneObject.frag
        GuroSceneObject.vert
        keyboard.cpp
        keyboard.hpp
        lightsource.hpp
        LightSource.vert
        main.cpp
        mainwindow.cpp
        mainwindow.hpp
        mainwindow.ui
        material.hpp
        materialfactory.hpp
        mesh.hpp
        meshfactory.cpp
        meshfactory.hpp
        meshobject.cpp
        meshobject.hpp
        object.hpp
        objectsgrid.cpp
        objectsgrid.hpp
        pointlightsource.cpp
        pointlightsource.hpp
        renderobject.hpp
        scene.cpp
        scene.hpp
        sceneobject.cpp
        sceneobject.hpp
        scenewidget.cpp
        scenewidget.hpp
        shaders.qrc
        spotlightsource.cpp
        spotlightsource.hpp
        vertex.hpp)

add_executable(kolodkin-task3 ${SRC_LIST})

find_package(Qt5 COMPONENTS Widgets REQUIRED)

target_link_libraries(kolodkin-task3 PRIVATE Qt5::Widgets)