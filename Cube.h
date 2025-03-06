#ifndef CUBE_H
#define CUBE_H

#include <vector>

#include "Object.h"
#include "Instance.h"

/**
 * @brief Cube template. 
 * First create an instance of this class. Then, through it, you can create real cube object. 
 * the vertices will stay the same, only the position / rotation / scaling in the world is changing.
 */
class Cube : public Object
{
private:

    const static int NB_VERTICES = 36;
    const static int NB_DATA_PER_VERTICE = 8;
    const static int NB_TO_DRAW = NB_VERTICES * NB_DATA_PER_VERTICE;

public:

    Cube(bool delay_init = false);
    ~Cube();
    void init();

    using Instance = _Instance;

private:

    std::vector<Instance> instances;

public:

    Instance& create(const Shader& shd);

protected:

    std::array<float, NB_VERTICES * NB_DATA_PER_VERTICE> vertices = {
        // pos                  // normals            // texture coordinates
        -0.5f, -0.5f, -0.5f,    0.0f, 0.0f, -1.0f,    0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,    0.0f, 0.0f, -1.0f,    1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,    0.0f, 0.0f, -1.0f,    1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,    0.0f, 0.0f, -1.0f,    1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,    0.0f, 0.0f, -1.0f,    0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,    0.0f, 0.0f, -1.0f,    0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,    0.0f, 0.0f,  1.0f,    0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,    0.0f, 0.0f,  1.0f,    1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,    0.0f, 0.0f,  1.0f,    1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,    0.0f, 0.0f,  1.0f,    1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,    0.0f, 0.0f,  1.0f,    0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,    0.0f, 0.0f,  1.0f,    0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,    -1.0f, 0.0f, 0.0f,    1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,    -1.0f, 0.0f, 0.0f,    1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,    -1.0f, 0.0f, 0.0f,    0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,    -1.0f, 0.0f, 0.0f,    0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,    -1.0f, 0.0f, 0.0f,    0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,    -1.0f, 0.0f, 0.0f,    1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,     1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 0.0f,     1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,     0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,     0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 0.0f,     0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,     1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,    0.0f, -1.0f, 0.0f,    0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,    0.0f, -1.0f, 0.0f,    1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,    0.0f, -1.0f, 0.0f,    1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,    0.0f, -1.0f, 0.0f,    1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,    0.0f, -1.0f, 0.0f,    0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,    0.0f, -1.0f, 0.0f,    0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,    0.0f,  1.0f, 0.0f,    0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,    0.0f,  1.0f, 0.0f,    1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,    0.0f,  1.0f, 0.0f,    1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,    0.0f,  1.0f, 0.0f,    1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,    0.0f,  1.0f, 0.0f,    0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,    0.0f,  1.0f, 0.0f,    0.0f, 1.0f
    };

    virtual std::array<float, NB_VERTICES * NB_DATA_PER_VERTICE>&
     get_vertices()
     { return vertices; }
};

#endif