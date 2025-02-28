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
#include <array>

#include "cmake_variables.h"
#include "debug_helper.h"

std::string get_file_content(std::string path);

class Shader
{
private:

    unsigned int shaderProgram;

    std::string name;

    bool loaded = false;

public:

    Shader();

    bool load(std::string vertex_path, std::string fragment_path, std::string _name);
    bool compile_vertexShader(unsigned int& vertexShader, std::string vertex_path);
    bool compile_fragmentShader(unsigned int& fragmentShader, std::string fragment_path);
    bool link_shaderProgram(unsigned int& vertexShader, unsigned int& fragmentShader);
    void destroy();
    bool is_loaded() const;

    void turn_on() const;
    unsigned int get_location(const char* uniform_name) const;
    void set_uniform(const char* uniform_name, float x, float y, float z, float w) const;
    void set_uniform(const char* uniform_name, bool value) const;
    void set_uniform(const char* uniform_name, int value) const;
    void set_uniform(const char* uniform_name, float value) const;
    void set_uniform(const char* uniform_name, glm::vec3 vec) const;
    void set_uniform(const char* uniform_name, glm::mat4 matrix) const;

private:

    const std::string MODEL = "model";
    const std::string VIEW  = "view";
    const std::string PROJECTION  = "projection";

public:

    void set_model(glm::mat4 model) const;
    void set_view(glm::mat4 view) const;
    void set_projection(glm::mat4 projection) const;
};

// TODO: as real enum
constexpr unsigned int NB_SHADER_TYPE = 2;
constexpr int OBJ_SHADER = 0;
constexpr int LIGHT_SHADER = 1;
using Shader_type = int;

const std::array<std::string, NB_SHADER_TYPE>
VERTEX_PATH {
    "../shaders/object.vshd",
    "../shaders/light_source.vshd"
},
FRAGMENT_PATH {
    "../shaders/object.fshd",
    "../shaders/light_source.fshd"
},
SHADER_NAME {
    "Simple Object shader",
    "Light shader"
};

#endif