#include "Object.h"

Object::Object(std::string const model_path, Shader& shd) : shader { shd }, model { model_path }
{

}

/**
 * @brief get the model matrix, which converts local coordinates to world coordinates
 * @return glm::mat4 the model matrix
 */
glm::mat4 Object::get_model_mat4() const
{
    glm::mat4 mat = glm::mat4(1.0f);
    mat = glm::translate(mat, pos);
    mat = glm::scale(mat, scaling);
    mat = glm::rotate(mat, rotation_angle, rotation_axis);
    return mat;
}

void Object::draw()
{
    shader.turn_on();
    
    // set world position of the object
    shader.set_model(get_model_mat4());
    shader.set_model_normals( glm::mat3(glm::transpose(glm::inverse( get_model_mat4() ))) );

    model.draw(shader);
}