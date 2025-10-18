#include "Model.h"
#include "Ressources.h"
#include <iostream>

Model::Model(const std::string path)
{
    load(path);
}

void Model::load(const std::string path)
{
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if(!scene || scene -> mFlags & AI_SCENE_FLAGS_INCOMPLETE || !(scene -> mRootNode))
    {
        std::cerr << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }

    dir = path.substr(0, path.find_last_of('/')) + "/";

    loadNode(scene -> mRootNode, scene);
}

/** 
 * @brief loads recursivly the model
 */
void Model::loadNode(aiNode *node, const aiScene *scene)
{
    // node's meshes
    for(unsigned int i = 0 ; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(loadMesh(mesh, scene));
    }

    // node's children's nodes
    for(unsigned int i = 0 ; i < node->mNumChildren; ++i)
        loadNode(node->mChildren[i], scene);
}

inline unsigned int max(unsigned int a, unsigned int b)
{
    return (a > b) ? a : b;
}

Mesh Model::loadMesh(aiMesh *mesh, const aiScene *scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<ressources::TEXTID> textures;

    // vertex positions, normals and texture coordinates
    for(unsigned int i = 0 ; i < mesh->mNumVertices ; ++i)
    {
        Vertex vertex;

        vertex.pos = get_vec3(mesh->mVertices[i]);
        vertex.normal = get_vec3(mesh->mNormals[i]);
        if(mesh->mTextureCoords[0])
        {
            vertex.textCoord.x = mesh->mTextureCoords[0][i].x;
            vertex.textCoord.y = mesh->mTextureCoords[0][i].y;
        }
        else
            vertex.textCoord = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }

    // process indices = order to draw coordinates to get the right primitives
    for(unsigned int i = 0 ; i < mesh->mNumFaces ; i++)
    {
        aiFace face = mesh->mFaces[i];

        for(unsigned int j = 0 ; j < face.mNumIndices ; j++)
            indices.push_back(face.mIndices[j]);
    }

    // process material (textures)
    if(mesh->mMaterialIndex >= 0)
    {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

        unsigned int specCount = material->GetTextureCount(aiTextureType_SPECULAR);
        unsigned int diffCount = material->GetTextureCount(aiTextureType_DIFFUSE);

        for(unsigned int i = 0 ; i < max(specCount, diffCount) ; ++i)
        {
            std::string diffPath, specPath;
            
            if(i < diffCount)
            {
                aiString path;
                material->GetTexture(aiTextureType_DIFFUSE, i, &path);
                diffPath = std::string(path.C_Str());
            }
            else
                diffPath = "../" + DEFAULT_TEXTURE_PATH;

            if(i < specCount)
            {
                aiString path;
                material->GetTexture(aiTextureType_SPECULAR, i, &path);
                specPath = std::string(path.C_Str());
            }
            else
                specPath = "../" + DEFAULT_TEXTURE_PATH;

            textures.push_back(ressources::get_texture(dir + diffPath, dir + specPath));
        }
    }

    return Mesh(vertices, indices, textures);
}


void Model::draw(Shader& shader)
{
    for(auto && it : meshes)
        it.draw(shader);
}
