#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <glad/glad.h>

#include <iostream>
#include <vector>

#include "Texture.h"
#include "Instance.h"
#include "Object.h"


/**
 * @brief Cube template. 
 * First create an instance of this class. Then, through it, you can create real cube object. 
 * the vertices will stay the same, only the position / rotation / scaling in the world is changing.
 */
class Cube : public Object
{
private:

    const static int NB_VERTICES = 36;
    const static int NB_DATA_PER_VERTICE = 5;
    const static int NB_TO_DRAW = NB_VERTICES * NB_DATA_PER_VERTICE;

public:

    Cube(bool && delay_init = false);
    ~Cube();

    void init();
    void destroy();

    void set(float new_vertices[NB_VERTICES]);
    void buffer();

    void draw(const Instance& to_draw);

    void remove_all_texture();
    void set_textures(std::vector<Texture> _textures);
    void bind_texture(Texture _texture);
    void add_texture(const char* path, bool && has_alpha_chanel);

private:

    // space on the GPU where vertices are stored, so that they can be efficiently passed to the shader
    unsigned int VBO;

    // remembers how a VBO is configured,
    // so that every changes we made to the VBO is restored by binding the VAO.
    // Therefore, we can use multiple VAO and switch between them to have multiple kind of display
    unsigned int VAO;

    // texture of the object
    std::vector<Texture> textures;
    std::vector<bool> texture_is_mine;

    float vertices[NB_VERTICES * NB_DATA_PER_VERTICE] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,   0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,   0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,   0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
};

#endif