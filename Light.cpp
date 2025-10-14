#include "Light.h"

// access static class member form the cpp file
size_t Light::nbLights = 0;


Light::Light(std::string const model_path, Shader& shd) : Object(model_path, shd)
{
    init();
}

Light::Light(std::string const model_path, Shader& shd, Light_spec const _spec) :
       Object(model_path, shd), spec { _spec }
{
    init();
}

Light::~Light()
{
    --nbLights;
}

void Light::init()
{
    iLight = nbLights;
    ++nbLights;
    std::cout << "init light " << iLight << " of " << iLight << std::endl;
}


void Light::draw()
{
    shader.turn_on();

    // set world position of the object
    shader.set_model(get_model_mat4());
    shader.set_model_normals( glm::mat3(glm::transpose(glm::inverse( get_model_mat4() ))) );

    shader.set_light(pos, spec, iLight);

    model.draw(shader);
}
