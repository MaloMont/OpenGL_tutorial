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
        instances.pop_back();

    destroy();

    loaded = false;
}

void Light::init()
{
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);  

    buffer();

    loaded = true;
}

/**
 * @brief creates a new Light instance
 * @param shd the linked shader
 * @return Light::LightInstance& a reference to the new instance
 */
Light::Instance& Light::create(const Shader& shd)
{
    instances.push_back({LIGHT, shd, LIGHT_DEFAULT_TEXTURE});
    return instances.back();
}

void Light::Instance::set_spec(Light_spec _spec)
{
    spec = _spec;
}

void Light::Instance::prepare_draw()
{
    shader.set_uniform("iLight", iLight);
}
