#include "World.h"

World::World()
{
    // the initialization is delayed so that it occurs after the initialization of the libraries
    templates[CUBE] = new Cube(true);
    templates[LIGHT] = new Light(true);
}

World::~World()
{
    for(auto && it : templates)
        delete it;
}

/**
 * @brief destroys the world :)
 */
void World::destroy()
{
    for(auto && it : templates)
        it->destroy();

    for(auto && itShader : shaders)
        itShader.destroy();
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
 * @brief update the light color
 * @param color the new color
 */
void World::update_light_color(glm::vec3 color)
{
    for(auto && itShader : shaders)
    {
        if(itShader.is_loaded())
        {
            itShader.set_uniform("light_color", color);
        }
    }
}

/**
 * @brief draws an object 
 * @param obj the object to draw
 */
void World::draw(const _Instance& obj)
{
    templates[obj.type] -> draw(obj);
}

