#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <glad/glad.h>
#include <string>

#include "Cube.h"


/**
 * @brief The light source 
 */
class Light : public Cube
{
private:

    const char* LIGHT_TEXTURE = "../assets/textures/light.png";

public:

    Light(bool delay_init = false);
    ~Light();
    void init();

private:
};

#endif