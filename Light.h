#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

#include "Object.h"
#include "Model.h"
#include "Shader.h"
#include "Light_spec.h"

class Light : public Object
{
public:

    Light(std::string const model_path, Shader& shd);
    Light(std::string const model_path, Shader& shd, Light_spec const spec);
    ~Light();

    void draw();

    Light_spec spec;

private:

    static size_t nbLights; // number of lights created
    int iLight;

    void init();
};

#endif