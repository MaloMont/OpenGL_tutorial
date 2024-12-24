#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>

#include "debug_helper.h"

std::string get_file_content(std::string path);

struct Shader
{
    unsigned int shaderProgram;

    bool loaded = false;

    Shader();

    bool load(std::string vertex_path, std::string fragment_path);
    bool compile_vertexShader(unsigned int& vertexShader, std::string vertex_path);
    bool compile_fragmentShader(unsigned int& fragmentShader, std::string fragment_path);
    bool link_shaderProgram(unsigned int& vertexShader, unsigned int& fragmentShader);

    void turn_on() const;
    unsigned int get_location(const char* uniform_name) const;
    void set_uniform(const char* uniform_name, float x, float y, float z, float w) const;
    void set_uniform(const char* uniform_name, bool value) const;
    void set_uniform(const char* uniform_name, int value) const;
    void set_uniform(const char* uniform_name, float value) const;
    void set_uniform(const char* uniform_name, glm::mat4 matrix) const;
};

#endif