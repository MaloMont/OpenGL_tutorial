#include "Ressources.h"

#include <vector>
#include <unordered_map>

#include "Texture.h"

namespace ressources
{

static const GLenum UNINITIALIZED_UNIT = GL_TEXTURE0 - 1;

struct Texture
{
    unsigned int diffuse_text;
    unsigned int specular_text;

    GLenum diffuse_unit = UNINITIALIZED_UNIT;
    GLenum specular_unit = UNINITIALIZED_UNIT;

    float shininess = 64.0f;

    bool loaded = false;
};

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


/**
 * @brief loads an OpenGL texture from the image at the given `path`
 * @param texture the texture's future emplacement : either diffuse_text or specular_text
 * @param path the path to the image, from the executable
 * @param has_alpha_canal whether the image has an alpha canal or not
 */
void partial_load(unsigned int& texture, const char* path)
{
    bool has_alpha_canal = img_has_alpha(path);

    // OpenGL expects another kind of y axis
    stbi_set_flip_vertically_on_load(true);

    int width, height, nbChannels;
    unsigned char *img = stbi_load(path, &width, &height, &nbChannels, 0); 
    if(not img)
    {
        std::cerr << "[ERROR]: couldn't load image " << path << std::endl;
        return;
    }

    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);

    // how a texture will take the whole triangle space
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // how the color will be chosen if the texture size does not correspond to the triangle size
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // when the texture is too small
    // when the texture is too big. Then, we use a mipmap, wich is the texture image given in multiple resolution.
    // here, we have linear interpolation between the two closest mipmap AND between the texture pixels colors
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    // 1: type of texture
    // 2: number of mipmap we want to define ourself the texture (here we let OpenGL do it)
    // 3: storage format of the texture
    // 4: width ; 5: height
    // 6: zero. just copy it.
    // 7, 8: format of the image we send
    // 9: the image.
    if(has_alpha_canal)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
    else
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);

    // generate a mipmap for the texture
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(img);
}

/**
 * @brief Get the texture id corresponding to the given pair of path. if one has already be created,
 * its id is returned ; else, a new texture is created, and its id is returned.
 * @param diffuse_path the path to the image of the diffuse texture
 * @param specular_path the path to the image og the specular texture
 * @return ID the id of the texture corresponding to the pair of path
 */
ID get_texture(const std::string diffuse_path, const std::string specular_path)
{
    std::string name = nameof(diffuse_path, specular_path);

    if(loaded(name))
        return find(name);

    Texture text;
    partial_load(text.diffuse_text, diffuse_path.c_str());
    partial_load(text.specular_text, specular_path.c_str());
    text.loaded = true;

    textures.push_back(text);

    ID id = textures.size() - 1;

    id_by_name.insert({name, id});

    return id;
}

/**
 * @brief Get the texture id corresponding to the given pair of path. if one has already be created,
 * its id is returned ; else, a new texture is created, and its id is returned.
 * @param diffuse_path the path to the image of the diffuse texture
 * @param specular_path the path to the image og the specular texture
 * @return ID the id of the texture corresponding to the pair of path
 */
ID get_texture(const Texture_spec spec)
{
    std::string diffuse_path = spec.diff_path, specular_path = spec.spec_path;

    std::string name = nameof(diffuse_path, specular_path);

    if(loaded(name))
        return find(name);

    Texture text;
    partial_load(text.diffuse_text, diffuse_path.c_str());
    partial_load(text.specular_text, specular_path.c_str());
    text.loaded = true;

    textures.push_back(text);

    ID id = textures.size() - 1;

    id_by_name.insert({name, id});

    return id;
}

/**
 * @brief activates and binds the given texture of the given units
 * @param id the id of the texture
 * @param diffuse_unit the unit for the diffuse texture
 * @param specular_unit the unit for the specular texture
 */
void activate(const ID id, const GLenum diffuse_unit, const GLenum specular_unit)
{
    if(id >= ressources::textures.size())
    {
        std::cerr << "[Error]: activate: invalid id: " << id << std::endl;
        return;
    }

    Texture& text = ressources::textures[id];

    if(not text.loaded)
    {
        std::cerr << "[WARNING]: activate: trying to activate an uninitialized texture." << std::endl;
        return;
    }

    text.diffuse_unit = diffuse_unit;
    glActiveTexture(text.diffuse_unit);
    glBindTexture(GL_TEXTURE_2D, text.diffuse_text);

    text.specular_unit = specular_unit;
    glActiveTexture(text.specular_unit);
    glBindTexture(GL_TEXTURE_2D, text.specular_text);
}

/**
 * @brief activates by name instead of by id
 */
void activate(const std::string name, const GLenum diffuse_unit, const GLenum specular_unit)
{
    ID id = find(name);

    if(id != ERROR_ID)
        activate( id, diffuse_unit, specular_unit );
}
/**
 * @brief desactivates the texture
 */
void desactivate(const ID id)
{
    if(id >= ressources::textures.size())
    {
        std::cerr << "[Error]: activate: invalid id: " << id << std::endl;
        return;
    }

    Texture& text = ressources::textures[id];

    if(text.diffuse_unit != UNINITIALIZED_UNIT)
    {
        glActiveTexture(text.diffuse_unit);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    text.diffuse_unit = UNINITIALIZED_UNIT;

    if(text.specular_unit != UNINITIALIZED_UNIT)
    {
        glActiveTexture(text.specular_unit);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    text.specular_unit = UNINITIALIZED_UNIT;
}

/**
 * @brief desactivates the texture
 */
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
    return ressources::textures[id].shininess;
}

float get_shininess(std::string name)
{
    return get_shininess(find(name));
}

void debug(ID id)
{
    std::cout << ressources::textures[id].diffuse_text << " and "
              << ressources::textures[id].specular_text
              << std::endl;
}


}