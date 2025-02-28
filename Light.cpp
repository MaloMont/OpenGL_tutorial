#include "Light.h"

Light::Light(bool delay_init /* = false */) : Cube(delay_init)
{
    if(not delay_init)
    {
        init();
    }
}

Light::~Light()
{
    if(not loaded)
        return;

    while(not instances.empty())
        instances.pop_back(); // nothing to destroy

    destroy();

    loaded = false;
}

void Light::init()
{
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);  

    buffer();

    add_texture(LIGHT_TEXTURE, true);

    loaded = true;
}

/**
 * @brief creates a new Light instance
 * @param shd the linked shader
 * @return Light::LightInstance& a reference to the new instance
 */
Light::Instance& Light::create(const Shader& shd)
{
    instances.push_back({LIGHT, shd});
    return instances.back();
}
