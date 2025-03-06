#ifndef LIGHT_DEF_H
#define LIGHT_DEF_H

#include <glm/glm.hpp>

/**
 * @brief describes a simple lightening
 */
struct Light_spec
{
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess = 0;
};

constexpr Light_spec DEFAULT_LIGHT {
    {0.75f, 0.6f, 0.2f},
    {1.0f, 0.8f, 0.55f},
    {1.0f, 1.0f, 1.0f}
};

#endif