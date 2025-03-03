#ifndef MATERIAL_H
#define MATERIAL_H

struct Material
{
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess = 0;
};

constexpr Material OBSIDIAN = {
    {0.05375f, 0.05f, 0.06625f},
    {0.18275f, 0.17f, 0.22525f},
    {0.332741f, 0.328634f, 0.346435f},
    0.3 * 128
};

constexpr Material PERSO = {
    {1.0f, 0.5f, 0.31f},
    {1.0f, 0.5f, 0.31f},
    {0.5f, 0.5f, 0.5f},
    32.0f
};

constexpr Material LAMP = {
    {0.8f, 0.8f, 0.25f},
    {0.8f, 0.8f, 0.8f},
    {1.1f, 1.1f, 1.1f},
    2048.0f
};

constexpr Material DEFAULT_LIGHT {
    {0.75f, 0.6f, 0.2f},
    {1.0f, 0.8f, 0.55f},
    {1.0f, 1.0f, 1.0f}
};

#endif