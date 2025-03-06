#ifndef TEXTURE_SPEC
#define TEXTURE_SPEC

struct Texture_spec
{
    const char* diff_path;
    const bool diff_has_alpha;
    const char* spec_path;
    const bool spec_has_alpha;
};

constexpr Texture_spec DEFAULT_TEXTURE {
    "../assets/textures/container2_diffuse.png", true,
    "../assets/textures/container2_specular.png", true
};

constexpr Texture_spec LIGHT_DEFAULT_TEXTURE {
    "../assets/textures/white.png", true,
    "../assets/textures/white.png", true
};

#endif