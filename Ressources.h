#ifndef RESSOURCES_H
#define RESSOURCES_H

#include <glad/glad.h>
#include <stb_image.h>
#include <iostream>
#include <cstring>

#include "Texture_spec.h"

constexpr std::string ASSETS = "../assets/";

namespace ressources
{
    using TEXTID = unsigned int;

    TEXTID get_texture(const std::string diffuse_path, const std::string specular_path);
    TEXTID get_texture(const Texture_spec spec);

    void activate(const TEXTID id, const GLenum diffuse_unit, const GLenum specular_unit);
    void activate(std::string name, const GLenum diffuse_unit, const GLenum specular_unit);
    void desactivate(TEXTID id);
    void desactivate(std::string name);

    float get_shininess(const TEXTID id);
    float get_shininess(std::string name);

    std::string nameof(const std::string diffuse_path, const std::string specular_path);

    void debug(TEXTID id);
}

#endif