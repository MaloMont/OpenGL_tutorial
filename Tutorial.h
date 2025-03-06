#ifndef TUTORIAL_H
#define TUTORIAL_H

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/random.hpp>

#include <iostream>
#include <math.h>

#include "cmake_variables.h"
#include "Callbacks.h"
#include "Shader.h"
#include "World.h"
#include "Camera.h"

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

    void mouse_callback(GLFWwindow* window, double xpos, double ypos);

private:

    auto setup(); // TODO: remove

    GLFWwindow* window;
    const int WIN_WIDTH = 800;
    const int WIN_HEIGHT = 600;

    World world;
    Camera camera = Camera(WIN_WIDTH, WIN_HEIGHT);

    float delta_time = 0.0f;	// Time between current frame and last frame

    float last_mouse_x = WIN_WIDTH / 2.;
    float last_mouse_y = WIN_HEIGHT / 2.;
    bool first_mouse = true;
};


#endif