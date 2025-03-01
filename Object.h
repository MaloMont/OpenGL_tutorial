#ifndef OBJECT_H
#define OBJECT_H

#include <glad/glad.h>

#include <iostream>
#include <vector>

#include "Texture.h"
#include "Instance.h"

/**
 * @brief Simple object template (abstract mother class)
 */
class Object
{
protected:

    const static int NB_VERTICES = 36;
    const static int NB_DATA_PER_VERTICE = 8;
    const static int NB_TO_DRAW = NB_VERTICES * NB_DATA_PER_VERTICE;

public:

    Object(bool delay_init = false);
    virtual ~Object();

    virtual void init();
    virtual void buffer();
    virtual void destroy();
    virtual bool is_loaded() const;

    virtual void draw(const _Instance& to_draw);

    virtual void remove_all_texture();
    virtual void set_textures(std::vector<Texture> _textures);
    virtual void bind_texture(Texture _texture);
    virtual void add_texture(const char* path, bool && has_alpha_chanel);

protected:

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

    virtual std::array<float, NB_VERTICES * NB_DATA_PER_VERTICE>&
     get_vertices()
     = 0;
};


/**
 * @brief structure générique permettant d'accéder au type Instance d'un Objet donné en template
 * @tparam Obj the object whose type we want
 */
template <typename Obj>
struct ObjectSpec {
    using InstanceType = typename Obj::Instance;
};


#endif