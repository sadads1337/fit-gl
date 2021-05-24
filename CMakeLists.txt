cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(fit-gl VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
    # disable warning for qt.
    add_compile_options(/wd5240)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_subdirectory(thirdparty)

include_directories(src)
add_subdirectory(src)
