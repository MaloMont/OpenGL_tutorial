#include "World.h"

World::World()
{  }

World::~World()
{
    destroy();
}

/**
 * @brief destroys the world :)
 */
void World::destroy()
{
    while(not objects.empty())
        objects.pop_back(); // maybe later we'll need to destroy it manually

    models.destroy();
}

/**
 * @brief creates an object of given type
 * @param type the type of the new object
 * @return Instance an instance class describing this new object
 */
Instance World::create(Obj_type type)
{
    if(not models[type].is_loaded())
        models[type].init();

    return Instance(type);
}

/**
 * @brief draws an object to the world
 * @param shader the shader used for this object
 * @param obj the object to be drawn in the world
 */
void World::draw(const Shader& shader, const Instance& obj)
{
    models[obj.type].draw(shader, obj);
}


/**
 * @brief destroys every model
 */
void World::Models::destroy()
{
    cube.destroy();
    object.destroy();
}

/**
 * @brief access the model for the given type
 * @param type the type of the model (like CUBE)
 * @return Object& a reference to the model
 */
Object& World::Models::operator[](Obj_type type)
{
    switch(type)
    {
        case CUBE:
            return cube;
        break;
        default:
            return object;
        break;
    }
}
