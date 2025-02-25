cmake_minimum_required(VERSION 3.10)

project(Tutorial VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Tutorial)
target_sources(Tutorial PRIVATE
    main.cpp
    Tutorial.cpp
    Callbacks.cpp
    Camera.cpp
    Shader.cpp
    Texture.cpp
    World.cpp
    Instance.cpp
    Object.cpp
    Cube.cpp
    Light.cpp
    debug_helper.cpp
    stb_image.cpp glad.c
)

# include glfw
add_subdirectory(glfw)
target_link_libraries(Tutorial glfw)

set(VERTEX_SHADER_FILE "\"../shaders/vertex_shader.glsl\"")
set(FRAGMENT_SHADER_FILE "\"../shaders/fragment_shader.glsl\"")

# pass project version to the code
target_include_directories(Tutorial PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           "${PROJECT_SOURCE_DIR}"
                           "${PROJECT_SOURCE_DIR}/glfw/include"
                          )
configure_file(cmake_variables.h.in cmake_variables.h)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g -pg -fsanitize=address")