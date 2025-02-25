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
    if(loaded)
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
