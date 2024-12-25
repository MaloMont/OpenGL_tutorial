#ifndef WORLD_H
#define WORLD_H

#include <array>
#include <vector>
#include <functional>

#include "Object.h"
#include "Cube.h"
#include "Instance.h"

class World
{
public:

    World();
    ~World();
    void destroy();
    Instance create(Obj_type type);
    void draw(const Shader& shader, const Instance& obj);

private:

    class Models
    {
    private:
        const static int NB_OBJ_TYPES = 1;
        constexpr static int UNINITIALIZED = -1;

        Cube cube = Cube(true);
        Object object;

    public:

        void destroy();
        Object& operator[](Obj_type type);
    };

    Models models;

    std::vector<Instance> objects;
};

#endif