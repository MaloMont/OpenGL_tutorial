#ifndef TUTORIAL_H
#define TUTORIAL_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <math.h>

#include "cmake_variables.h"
#include "Callbacks.h"
#include "Cube.h"
#include "Shader.h"

#include "debug_helper.h"

class Tutorial
{
public:

    Tutorial();
    ~Tutorial();
    void init_glfw();
    void init_glad();
    void init_libraries();
    void process_input();
    void render_loop();

private:

    GLFWwindow* window;
    int WIN_WIDTH = 800, WIN_HEIGHT = 600;

    Shader shader;

    // delying initialization to after the libraries are initialized
    Cube cube_template = Cube(true);
};

#endif