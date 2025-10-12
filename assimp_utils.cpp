#include "assimp_utils.h"

const glm::vec3 get_vec3(aiVector3D vec)
{
    return glm::vec3(vec.x, vec.y, vec.z);
}
