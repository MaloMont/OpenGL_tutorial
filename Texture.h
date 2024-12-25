#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <stb_image.h>
#include <iostream>

#include "Shader.h"

class Texture
{
public:

    Texture(GLenum _unit, const char* path, bool && has_alpha_canal);
    void load(const char* path, bool && has_alpha_canal);

    void activate(const Shader& shader);
    void desactivate(const Shader& shader);
    void destroy();

    unsigned int get_id() const;

private:

    unsigned int texture;
    GLenum unit;
};

#endif