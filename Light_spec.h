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
    float shininess = 0.0f;

    bool is_at_infinity = false;
    glm::vec3 direction;

    bool is_spotlight = false;
    float inner_cutoff = 0.0f; // cos of the angle of the fully lightened cone
    float outer_cutoff = 0.0f; // cos of the max angle lightening fragments

    struct Attenuation
    {
        // default: covers a distance of ~50
        float constant  = 1.0f;
        float linear    = 0.09f;
        float quadratic = 0.032f;
    }
    attenuation;
};

constexpr Light_spec DEFAULT_LIGHT {
    {0.4f, 0.3f, 0.2f},
    {1.0f, 0.8f, 0.55f},
    {1.0f, 1.0f, 1.0f},
    32.0f,
    false, {0.0f, 0.0f, 0.0f},
    false, 0.0f, 0.0f,
    {1.0f, 0.09f, 0.032f}
};

constexpr Light_spec SUN_LIGHT {
    {0.3f, 0.3f, 0.3f},
    {0.5f, 0.5f, 0.5f},
    {0.8f, 0.8f, 0.8f},
    0.0f,
    true, {-1.0f, 0.0f, 0.0f},
    false, 0.0f, 0.0f,
    {1.0f, 0.0f, 0.0f}
};

constexpr Light_spec SPOT_LIGHT {
    {0.4f, 0.3f, 0.2f},
    {1.0f, 0.6f, 0.55f},
    {1.0f, 1.0f, 1.0f},
    32.0f,
    false, {0.0f, 0.0f, -1.0f},
    true, glm::cos(glm::radians( 12.5f )), glm::cos(glm::radians( 25.0f )),
    {1.0f, 0.045f, 0.075f}
};

#endif