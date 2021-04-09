set(TASK4_SRCS
        main.cpp

        shaders.qrc
        colorowner.cpp colorowner.h coub.cpp coub.h coubsArmyWidget.cpp coubsArmyWidget.h object.cpp object.h objectmodel.cpp objectmodel.h sourcelight.cpp sourcelight.h sphere.cpp sphere.h normals.cpp normals.h mainwindow.cpp mainwindow.h mainwindow.ui)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_executable(Task2 ${PROJECT_SOURCES} ${UI_HEADERS})
add_executable(Task4 ${TASK4_SRCS})

target_link_libraries(Task4
        PRIVATE
        Qt5::Widgets
        FGL::Base
        )

