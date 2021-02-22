find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(devyatovskayaTask1
        main.cpp
        plainobject3d.cpp
        plainobject3d.h
        CubeObject.h
        cubeedges.cpp
        cubeedges.h
        cube.cpp
        cube.h
        cubewindow.cpp
        cubewindow.h
)

target_link_libraries(devyatovskayaTask1 
	PRIVATE Qt5::Widgets
	PUBLIC FGL::Base
)
