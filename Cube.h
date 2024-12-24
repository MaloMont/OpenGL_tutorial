#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <glad/glad.h>

#include <iostream>
#include <vector>

#include "Texture.h"


/**
 * @brief Cube template. 
 * First create an instance of this class. Then, through it, you can create real cube object. 
 * the vertices will stay the same, only the position / rotation / scaling in the world is changing.
 */
class Cube
{
private:

    const static int NB_VERTICES = 36;
    const static int NB_DATA_PER_VERTICE = 5;
    const static int NB_TO_DRAW = NB_VERTICES * NB_DATA_PER_VERTICE;

    // specific to each cube
    struct Instance
    {
        Instance(glm::vec3 _pos = glm::vec3(0.0f, 0.0f, 0.0f),
                 glm::vec3 _scaling = glm::vec3(1.0f, 1.0f, 1.0f),
                 glm::vec3 _rotation_axis = glm::vec3(1.0f, 0.0f, 0.0f),
                 float _rotation_angle = 0.0f);

        glm::vec3 pos;
        glm::vec3 scaling;
        glm::vec3 rotation_axis;
        float rotation_angle;

        glm::mat4 get_model_mat4() const;
    };

    std::vector<Instance> instances;

public:

    Cube(bool delay_init = false);
    ~Cube();

    void init();
    void destroy();

    void set(float new_vertices[NB_VERTICES]);
    void buffer();

    void draw(const Shader& shader);
    void draw(const Shader& shader, unsigned int iInstance_to_draw);

    void remove_all_texture();
    void set_textures(std::vector<Texture> _textures);
    void bind_texture(Texture _texture);
    void add_texture(const char* path, bool has_alpha_chanel);

    unsigned int create_instance(glm::vec3 _pos = glm::vec3(0.0f, 0.0f, 0.0f),
                                 glm::vec3 _scaling = glm::vec3(1.0f, 1.0f, 1.0f),
                                 glm::vec3 _rotation_axis = glm::vec3(1.0f, 0.0f, 0.0f),
                                 float _rotation_angle = 0.0f);
    void set_instance_pos(unsigned int iInstance, glm::vec3 _pos);
    void set_instance_scaling(unsigned int iInstance, glm::vec3 _scaling);
    void set_instance_rotation_axis(unsigned int Iinstance, glm::vec3 _rotation_axis);
    void set_instance_rotation_angle(unsigned int iInstance, float _rotation_angle);
    Instance get_instance(unsigned int iInstance);

private:

    bool loaded = false;

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