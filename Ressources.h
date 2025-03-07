#ifndef RESSOURCES_H
#define RESSOURCES_H

#include <glad/glad.h>
#include <stb_image.h>
#include <iostream>
#include <cstring>

#include "Texture_spec.h"

namespace ressources
{
    using ID = unsigned int;

    ID get_texture(const std::string diffuse_path, const std::string specular_path);
    ID get_texture(const Texture_spec spec);

    void activate(const ID id, const GLenum diffuse_unit, const GLenum specular_unit);
    void activate(std::string name, const GLenum diffuse_unit, const GLenum specular_unit);
    void desactivate(ID id);
    void desactivate(std::string name);

    float get_shininess(const ID id);
    float get_shininess(std::string name);

    std::string nameof(const std::string diffuse_path, const std::string specular_path);

    void debug(ID id);
}

#endif