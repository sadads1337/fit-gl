# Adding some hardcoded thirdparty libs
add_subdirectory(GSL)
include_directories(GSL/include)

add_subdirectory(glm)
include_directories(glm)

# Disable warnings from thirdparty libs
target_compile_options(GSL INTERFACE -Wno-error)
target_compile_options(glm INTERFACE -Wno-error)
