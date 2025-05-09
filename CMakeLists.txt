cmake_minimum_required(VERSION 3.16)
project(IMAC_project_digger)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)

add_executable(digger
    src/main.cpp
    src/renderer.cpp
    src/mapGenerator.cpp
)

target_include_directories(digger PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(digger glfw ${OPENGL_LIBRARIES})