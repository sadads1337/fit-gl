set(BiryuchkovTask3_SRCS

        main.cpp colorowner.cpp colorowner.h sourcelight.cpp sourcelight.h mainwindow.cpp mainwindow.h mainwindow.ui objectmodel.cpp objectmodel.h object.cpp object.h normals.cpp normals.h coubsArmyWidget.cpp coubsArmyWidget.h coub.cpp coub.h coubarmy.cpp coubarmy.h)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(BiryuchkovTask3 ${BiryuchkovTask3_SRCS})

target_link_libraries(BiryuchkovTask3
        PRIVATE
        Qt5::Widgets
        ${OPENGL_LIBRARIES}
        FGL::Base
        )

include_directories( ${OPENGL_INCLUDE_DIRS})

qt5_wrap_ui(UI_HEADERS mainwindow.ui)


