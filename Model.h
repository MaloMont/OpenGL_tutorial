#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>
#include <cmath>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "assimp_utils.h"

#include "Shader.h"
#include "Mesh.h"

class Model
{
public:

    Model(const std::string path);

    void draw(Shader& shader);

private:

    void load(const std::string path);
    void loadNode(aiNode *node, const aiScene *scene);
    Mesh loadMesh(aiMesh *mesh, const aiScene *scene);

    std::vector<Mesh> meshes;

    std::string dir;
};

#endif