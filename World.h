#ifndef WORLD_H
#define WORLD_H

#include <array>
#include <vector>
#include <functional>

#include "Object.h"
#include "Cube.h"
#include "Light.h"
#include "Shader.h"
#include "Instance.h"

class World
{
public:

    World();
    ~World();
    void destroy();

    Instance create(const Obj_type obj_type, const Shader_type shd_type);

    void update_shaders(glm::mat4 view, glm::mat4 projection);
    void draw(const Instance& obj);

private:

    class Models
    {
    private:

        const static int NB_OBJ_TYPES = 1;
        constexpr static int UNINITIALIZED = -1;

        Cube cube     = Cube(true);
        Object object = Object(true);
        Light light   = Light(true);

    public:

        void destroy();
        Object& operator[](Obj_type type);
    };

    Models models;

    std::vector<Instance> objects;

    std::array<Shader, NB_SHADER_TYPE> shaders;
};

#endif