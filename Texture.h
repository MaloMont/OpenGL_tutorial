#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <stb_image.h>
#include <iostream>
#include <cstring>

#include "Texture_spec.h"

static const GLenum UNINITIALIZED_UNIT = GL_TEXTURE0 - 1;

class Texture
{
public:

    Texture();
    Texture(const char* diff_path, const bool diff_has_alpha, const char* spec_path, const bool spec_has_alpha);
    Texture(Texture_spec spec);
    ~Texture();

    void activate(const GLenum _diffuse_unit, const GLenum _specular_unit);
    void desactivate();
    void destroy();

    void load(const char* diff_path, const bool diff_has_alpha, const char* spec_path, const bool spec_has_alpha);
    void load(Texture_spec spec);

    float get_shininess() const;

    unsigned int diffuse_text;
    unsigned int specular_text;

private:

    Texture(const Texture &) = delete;
    Texture(Texture &&) noexcept = delete;
    Texture& operator=(const Texture &) = delete;
    Texture& operator=(Texture &&) noexcept = delete;

    void partial_load(unsigned int& texture, const char* path, const bool has_alpha_canal);

    float shininess = 0.2f;

    GLenum diffuse_unit = UNINITIALIZED_UNIT;
    GLenum specular_unit = UNINITIALIZED_UNIT;

    bool loaded = false;
};

#endif