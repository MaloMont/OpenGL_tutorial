#ifndef MESH_H
#define MESH_H

#include <vector>
#include <glm/glm.hpp>
#include "Ressources.h"
#include "Shader.h"

struct Vertex
{
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec2 textCoord;
};

class Mesh
{
public:

    Mesh(std::vector<Vertex> _vertices, std::vector<unsigned int> _indices, std::vector<ressources::TEXTID> _texture);

    void init();
    void draw(Shader& shader);

private:

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<ressources::TEXTID> texture; // une seule texture...

    unsigned int VAO, VBO, EBO;
};

#endif