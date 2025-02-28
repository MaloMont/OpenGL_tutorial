#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

#include "Cube.h"

/**
 * @brief The light source 
 */
class Light : public Cube
{
private:

    const char* LIGHT_TEXTURE = "../assets/textures/light.png";

public:

    Light(bool delay_init = false);
    ~Light();
    void init();

    struct Instance : _Instance
    {
        using _Instance::_Instance;

        glm::vec3 color = {1.0f, 1.0f, 1.0f};

        void setColor(glm::vec3 new_color)
        { color = new_color; }
    };

private:

    std::vector<Instance> instances;
    using Cube::vertices;
    using Cube::get_vertices;

public:

    Instance& create(const Shader& shd);
};

#endif