#ifndef TRIANGLE_H
#define TRIANGLE_H

/** TODO
 * définir pour chaque texture si elle doit être libérée à la destruction de l'obect (<=> la texture est spécifique à cet objet)
 */

#include <glad/glad.h>

#include <iostream>
#include <vector>

#include "Texture.h"


struct Triangle
{
    const static int NB_VERTICES = 4;
    const static int NB_DATA_PER_VERTICE = 8;

    float vertices[NB_VERTICES * NB_DATA_PER_VERTICE] = {
        // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,    1.0f, 0.0f, 0.0f,   2.0f, 2.0f,   // top right
        0.5f, -0.5f, 0.0f,    0.0f, 1.0f, 0.0f,   2.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 2.0f    // top left 
    };

    // order
    unsigned int indices[6] = {
        0, 1, 3,
        1, 2, 3
    };

    // space on the GPU where vertices are stored, so that they can be efficiently passed to the shader
    unsigned int VBO;

    // remembers how a VBO is configured,
    // so that every changes we made to the VBO is restored by binding the VAO.
    // Therefore, we can use multiple VAO and switch between them to have multiple kind of display
    unsigned int VAO;

    // remembers the order to print the vertices (may use multiple times the same vertice)
    unsigned int EBO;

    // texture of the object
    std::vector<Texture> textures;
    std::vector<bool> texture_is_mine;

    Triangle();
    ~Triangle();

    void set(float new_vertices[NB_VERTICES]);
    void buffer();
    void draw(const Shader& shader);

    void remove_all_texture();
    void set_textures(std::vector<Texture> _textures);
    void bind_texture(Texture _texture);
    void add_texture(const char* path, bool has_alpha_chanel);
};

#endif