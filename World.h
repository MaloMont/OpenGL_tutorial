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

    /**
     * @brief creates a new object : an instance of some object template
     * 
     * @tparam Obj the type of the object template
     * @param obj_type also the type of the object template
     * @param shd_type the shader whith wich the object will be created
     * @return a reference to the new object
     */
    template<typename Obj>
    typename ObjectSpec<Obj>::InstanceType
    create(const Obj_type obj_type, const Shader_type shd_type)
    {
        if(not templates[obj_type] -> is_loaded())
            templates[obj_type] -> init();

        if(not shaders[shd_type].is_loaded())
            shaders[shd_type].load(VERTEX_PATH[shd_type], FRAGMENT_PATH[shd_type], SHADER_NAME[shd_type]);

        return static_cast<Obj*>( templates[obj_type] ) -> create(shaders[shd_type]);
    }

    void update_shaders(glm::mat4 view, glm::mat4 projection);
    void update_light_color(glm::vec3 color);

    void draw(const _Instance& obj);

private:

    std::array<Object*, NB_OBJ_TYPES> templates;

    std::array<Shader, NB_SHADER_TYPE> shaders;
};

#endif