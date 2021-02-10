set(MODULE_NAME "task1_makarov")

add_executable(${MODULE_NAME} main.cpp)

if (NOT MSVC)

# Run my concurrent code with thread sanitizer
target_compile_options(${MODULE_NAME} PRIVATE -g -O1 -fsanitize=thread)
target_link_options(${MODULE_NAME} PRIVATE -fsanitize=thread)

endif()
