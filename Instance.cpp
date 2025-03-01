#include "Instance.h"

/**
 * @brief constructor for an instance of cube
 */
_Instance::_Instance(const Obj_type _type,
                   const Shader& _shader,
                   glm::vec3 _pos /* = glm::vec3(0.0f, 0.0f, 0.0f) */,
                   glm::vec3 _scaling /* glm::vec3(1.0f, 1.0f, 1.0f) */,
                   glm::vec3 _rotation_axis /* = glm::vec3(1.0f, 0.0f, 0.0f) */,
                   float _rotation_angle /* = 0.0f */) :
          shader { _shader },
          type { _type },
          pos { _pos },
          scaling { _scaling },
          rotation_axis { _rotation_axis },
          rotation_angle { _rotation_angle }
{  }

/**
 * @brief get the model matrix, which converts local coordinates to world coordinates
 * @return glm::mat4 the model matrix
 */
glm::mat4 _Instance::get_model_mat4() const
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, pos);
    model = glm::scale(model, scaling);
    model = glm::rotate(model, rotation_angle, rotation_axis);
    return model;
}
