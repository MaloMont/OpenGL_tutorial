#include "Ressources.h"

#include <vector>
#include <unordered_map>

#include "Texture.h"

namespace ressources
{

static std::vector<Texture> textures;
static std::unordered_map<std::string, ID> id_by_name;

constexpr static ID ERROR_ID = (1 << 14);


std::string nameof(const std::string diffuse_path, const std::string specular_path)
{
    return diffuse_path + specular_path;
}

bool loaded(const std::string name)
{
    return ressources::id_by_name.find(name) != ressources::id_by_name.end();
}

bool loaded(const std::string diffuse_path, const std::string specular_path)
{
    return loaded(nameof(diffuse_path, specular_path));
}

ID find(std::string name)
{
    auto id = ressources::id_by_name.find(name);

    if(id == ressources::id_by_name.end())
    {
        std::cerr << "[Error]: desactivate: unknown texture name \'" << name << "\'" << std::endl;
        return ERROR_ID;
    }

    return (*id).second;
}

bool img_has_alpha(const std::string path)
{
    return path[path.size() - 2] == 'n';
}

ID get_texture(const std::string diffuse_path, const std::string specular_path)
{
    std::string name = nameof(diffuse_path, specular_path);

    if(loaded(name))
        return find(name);

    bool diffuse_has_alpha  = img_has_alpha(diffuse_path);
    bool specular_has_alpha = img_has_alpha(specular_path);
    textures.push_back(Texture(diffuse_path.c_str(), diffuse_has_alpha, specular_path.c_str(), specular_has_alpha));

    ID id = textures.size() - 1;

    id_by_name.insert({name, id});

    return id;
}

ID get_texture(const Texture_spec spec)
{
    std::string diffuse_path = spec.diff_path, specular_path = spec.spec_path;

    std::string name = nameof(diffuse_path, specular_path);

    if(loaded(name))
        return find(name);

    bool diffuse_has_alpha  = spec.diff_has_alpha;
    bool specular_has_alpha = spec.spec_has_alpha;
    textures.push_back(Texture(diffuse_path.c_str(), diffuse_has_alpha, specular_path.c_str(), specular_has_alpha));

    ID id = textures.size() - 1;

    id_by_name.insert({name, id});

    return id;
}

void activate(const ID id, const GLenum diffuse_unit, const GLenum specular_unit)
{
    if(id >= ressources::textures.size())
    {
        std::cerr << "[Error]: activate: invalid id: " << id << std::endl;
        return;
    }

    ressources::textures[id].activate(diffuse_unit, specular_unit);
}

void activate(const std::string name, const GLenum diffuse_unit, const GLenum specular_unit)
{
    ID id = find(name);

    if(id != ERROR_ID)
        activate( id, diffuse_unit, specular_unit );
}

void desactivate(const ID id)
{
    if(id >= ressources::textures.size())
    {
        std::cerr << "[Error]: activate: invalid id: " << id << std::endl;
        return;
    }

    ressources::textures[id].desactivate();
}

void desactivate(const std::string name)
{
    ID id = find(name);

    if(id == ERROR_ID)
    {
        std::cerr << "[Error]: desactivate: unknown texture name \'" << name << "\'" << std::endl;
        return;
    }

    desactivate(id);
}

float get_shininess(const ID id)
{
    return ressources::textures[id].get_shininess();
}

float get_shininess(std::string name)
{
    return get_shininess(find(name));
}

}