#ifndef INSTANCE_H
#define INSTANCE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Obj_type.h"
#include "Ressources.h"
#include "Texture_spec.h"

// specific to each object
struct _Instance
{
    _Instance(const Obj_type _type,
             const Shader& _shader,
             const Texture_spec _text,
             glm::vec3 _pos = glm::vec3(0.0f, 0.0f, 0.0f),
             glm::vec3 _scaling = glm::vec3(1.0f, 1.0f, 1.0f),
             glm::vec3 _rotation_axis = glm::vec3(1.0f, 0.0f, 0.0f),
             float _rotation_angle = 0.0f);

    ~_Instance();

    Obj_type type;

    const Shader& shader;

    ressources::ID texture;

    glm::vec3 pos;         
    glm::vec3 scaling;
    glm::vec3 rotation_axis;
    float rotation_angle;

    glm::mat4 get_model_mat4() const;
    void set_texture(ressources::ID id);
    virtual void prepare_draw();
};

#endif