#include "Cube.h"

/**
 * @brief Construct a new object by initializing the VBO, the VAO and the EBO
 */

Cube::Cube(bool delay_init /* = false */) : Object(delay_init)
{
    if(not delay_init)
        init();
}

/**
 * @brief Destroy the object by freeing its VAO, its VBO and its EBO (only if the object is loaded)
 */
Cube::~Cube()
{
    if(not loaded)
        return;

    while(not instances.empty())
        instances.pop_back();

    destroy();

    loaded = false;
}

/**
 * @brief initializes the cube template
 */
void Cube::init()
{
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);  

    buffer();

    loaded = true;
}

/**
 * @brief creates a new Cube instance
 * @param shd the linked shader
 * @return Cube::CubeInstance& a reference to the new instance
 */
Cube::Instance& Cube::create(const Shader& shd)
{
    instances.push_back({CUBE, shd, DEFAULT_TEXTURE});
    return instances.back();
}
