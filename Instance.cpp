#include "Instance.h"

/**
 * @brief constructor for an instance of cube
 */
Instance::Instance(Obj_type _type,
                   glm::vec3 _pos /* = glm::vec3(0.0f, 0.0f, 0.0f) */,
                   glm::vec3 _scaling /* glm::vec3(1.0f, 1.0f, 1.0f) */,
                   glm::vec3 _rotation_axis /* = glm::vec3(1.0f, 0.0f, 0.0f) */,
                   float _rotation_angle /* = 0.0f */)
{
    type = _type;
    pos = _pos;
    scaling = _scaling;
    rotation_axis = _rotation_axis;
    rotation_angle = _rotation_angle;
}


glm::mat4 Instance::get_model_mat4() const
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, pos);
    model = glm::scale(model, scaling);
    model = glm::rotate(model, rotation_angle, rotation_axis); 
    return model;
}

