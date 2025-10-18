#ifndef TEXTURE_SPEC
#define TEXTURE_SPEC

#include <string>

struct Texture_spec
{
    const char* diff_path;
    const bool diff_has_alpha;
    const char* spec_path;
    const bool spec_has_alpha;
};

const std::string DEFAULT_TEXTURE_PATH = "textures/black.png";

/* TODO: --> relative from ASSETS */

constexpr Texture_spec DEFAULT_TEXTURE {
    "../assets/textures/container2_diffuse.png", true,
    "../assets/textures/container2_specular.png", true
};    

constexpr Texture_spec LIGHT_DEFAULT_TEXTURE {
    "../assets/textures/white.png", true,
    "../assets/textures/white.png", true
};

#endif