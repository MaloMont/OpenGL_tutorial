#include "Texture.h"

#include "debug_helper.h"


/**
 * @brief Destroys the Texture object
 */
Texture::~Texture()
{
    destroy();
}

/**
 * @brief activates the texture
 */
void Texture::activate(const GLenum _diffuse_unit, const GLenum _specular_unit)
{
    if(not loaded)
    {
        std::cerr << "[WARNING]: Texture::activate: trying to activate an uninitialized texture." << std::endl;
        return;
    }

    std::cout << diffuse_text << ", " << specular_text << std::endl;

    diffuse_unit = _diffuse_unit;
    glActiveTexture(diffuse_unit);
    glBindTexture(GL_TEXTURE_2D, diffuse_text);

    specular_unit = _specular_unit;
    glActiveTexture(specular_unit);
    glBindTexture(GL_TEXTURE_2D, specular_text);
}

/**
 * @brief activates the texture
 */
void Texture::desactivate()
{
    if(diffuse_unit != UNINITIALIZED_UNIT)
    {
        glActiveTexture(diffuse_unit);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    diffuse_unit = UNINITIALIZED_UNIT;

    if(specular_unit != UNINITIALIZED_UNIT)
    {
        glActiveTexture(specular_unit);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    specular_unit = UNINITIALIZED_UNIT;
}

/**
 * @brief destroys the texture
 */
void Texture::destroy()
{
    if(not loaded)
        return;

    desactivate();

    // no problems if the text are uninitialized (ie diffuse_text & specular_text = -1)
    glDeleteTextures(1, &diffuse_text);
    glDeleteTextures(1, &specular_text);

    std::cout << "destroying texture \n";

    int *a = NULL;
    std::cout << *a;

    loaded = false;
}

/**
 * @brief getter for the shininess param of the texture
 */
float Texture::get_shininess() const
{
    return shininess;
}
