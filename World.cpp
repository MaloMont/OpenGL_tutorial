#include "World.h"

World::World()
{  }

World::~World()
{  }

/**
 * @brief destroys the world :)
 */
void World::destroy()
{
    while(not objects.empty())
        objects.pop_back(); // maybe later we'll need to destroy it manually

    for(auto && itShader : shaders)
        itShader.destroy();

    models.destroy();
}

/**
 * @brief creates an object of given type
 * @param type the type of the new object
 * @return Instance an instance class describing this new object
 */
Instance World::create(const Obj_type obj_type, const Shader_type shd_type)
{
    if(not models[obj_type].is_loaded())
        models[obj_type].init();

    if(not shaders[shd_type].is_loaded())
        shaders[shd_type].load(VERTEX_PATH[shd_type], FRAGMENT_PATH[shd_type]);

    return Instance(obj_type, shaders[shd_type]);
}

/**
 * @brief update the shaders with the new view and projection matrix 
 * @param view the new view matrix
 * @param projection the new projection matrix
 */
void World::update_shaders(glm::mat4 view, glm::mat4 projection)
{
    for(auto && itShader : shaders)
    {
        if(itShader.is_loaded())
        {
            itShader.set_view(view);
            itShader.set_projection(projection);
        }
    }
}

/**
 * @brief draws an object to the world
 * @param shader the shader used for this object
 * @param obj the object to be drawn in the world
 */
void World::draw(const Instance& obj)
{
    models[obj.type].draw(obj);
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
