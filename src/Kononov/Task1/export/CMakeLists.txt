find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_library(KononovTask1_export FirstShader.hpp)

target_link_libraries(KononovTask1_export
        PRIVATE Qt5::Widgets
        PUBLIC Kononov::Common)

target_include_directories(KononovTask1_export
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(Kononov::Task1::export ALIAS KononovTask1_export)
