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
#include "Light_spec.h"
#include "Ressources.h"

std::string get_file_content(std::string path);

class Shader
{
private:

    unsigned int shaderProgram;

    std::string name;

    bool loaded = false;

    const char* MODEL         = "model";
    const char* VIEW          = "view";
    const char* PROJECTION    = "projection";
    const char* MODEL_NORMALS = "model_normals";

    const char* VIEW_POS = "View_pos";

    const char* LIGHT_POS      = "light.pos";
    const char* LIGHT_AMBIENT  = "light.ambient";
    const char* LIGHT_DIFFUSE  = "light.diffuse";
    const char* LIGHT_SPECULAR = "light.specular";

    const char* MATERIAL_DIFFUSE_MAP  = "material.diffuse";
    const int   DIFFUSE_UNIT          = 0;
    const char* MATERIAL_SPECULAR_MAP = "material.specular";
    const int   SPECULAR_UNIT         = 1;
    const char* MATERIAL_SHININESS    = "material.shininess";

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
    void set_uniform(const char* uniform_name, glm::mat3 matrix) const;

    void set_view_pos(glm::vec3 view_pos) const;
    void set_model(glm::mat4 model) const;
    void set_view(glm::mat4 view) const;
    void set_projection(glm::mat4 projection) const;
    void set_model_normals(glm::mat3 model_normals) const;
    void activate(ressources::ID id) const;
    void desactivate(ressources::ID id) const;
    void set_light(glm::vec3 pos, Light_spec spec) const;

    std::string get_name() const { return name; }
};

// TODO: as real enum
constexpr unsigned int NB_SHADER_TYPE = 2;
constexpr int OBJ_SHADER = 0;
constexpr int LIGHT_SHADER = 1;
using Shader_type = int;

const std::array<std::string, NB_SHADER_TYPE>
VERTEX_PATH {
    "../shaders/object.vshd",
    "../shaders/object.vshd"
},
FRAGMENT_PATH {
    "../shaders/object.fshd",
    "../shaders/object.fshd"
},
SHADER_NAME {
    "Simple Object shader",
    "Light shader"
};

#endif