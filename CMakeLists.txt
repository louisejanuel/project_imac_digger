cmake_minimum_required(VERSION 3.16)
project(IMAC_project_digger)

set(CMAKE_CXX_STANDARD 17)

# Inclure les headers GLFW
include_directories(lib/glfw-3.4.bin.WIN64/include)

# Lier le dossier contenant glfw3.lib
link_directories(${CMAKE_SOURCE_DIR}/lib/glfw-3.4.bin.WIN64/lib-vc2022)

# Executable
add_executable(digger
    src/main.cpp
    src/MapGenerator.cpp
    src/Renderer.cpp
)

# Lier les librairies nécessaires
target_link_libraries(digger glfw3 opengl32)
