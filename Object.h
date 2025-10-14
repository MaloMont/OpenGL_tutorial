#ifndef OBJECT_H
#define OBJECT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

#include "Model.h"
#include "Shader.h"

class Object
{
public:

    Object(std::string const model_path, Shader& shd);

    glm::vec3 pos = {0.0f, 0.0f, 0.0f};
    glm::vec3 scaling = {1.0f, 1.0f, 1.0f};
    glm::vec3 rotation_axis = {1.0f, 0.0f, 0.0f};
    float rotation_angle = 0.0f;

    glm::mat4 get_model_mat4() const;

    void draw();

protected:

    Shader& shader;
    Model model;
};

#endif