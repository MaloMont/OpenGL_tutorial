#ifndef INSTANCE_H
#define INSTANCE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Obj_type.h"

// specific to each cube
struct Instance
{
    Instance(Obj_type _type,
             glm::vec3 _pos = glm::vec3(0.0f, 0.0f, 0.0f),
             glm::vec3 _scaling = glm::vec3(1.0f, 1.0f, 1.0f),
             glm::vec3 _rotation_axis = glm::vec3(1.0f, 0.0f, 0.0f),
             float _rotation_angle = 0.0f);

    glm::vec3 pos;
    glm::vec3 scaling;
    glm::vec3 rotation_axis;
    float rotation_angle;

    Obj_type type;

    glm::mat4 get_model_mat4() const;
};

#endif