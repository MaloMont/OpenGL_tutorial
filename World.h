#ifndef WORLD_H
#define WORLD_H

#include <array>
#include <vector>
#include <functional>

#include "Shader.h"

class World
{
public:

    World();
    ~World();
    void destroy();

    void update_shaders(glm::mat4 view, glm::mat4 projection);
    void update_light_conf(glm::vec3 pos, Light_spec spec, int iLight);
    void update_view_pos(glm::vec3 view_pos);

    Shader& get_shader(const Shader_type shd_type);

private:

    std::array<Shader, NB_SHADER_TYPE> shaders;
};

#endif