#include "Texture.h"

/**
 * @brief Construct a new Texture object
 * @param _unit the texture unit through wich the texture will be sent to the shader
 * @param path the path of the texture image
 * @param has_alpha_canal whether the image has an alpha canal or not
 */
Texture::Texture(GLenum _unit, const char* path, bool && has_alpha_canal)
{
    unit = _unit;
    load(path, std::forward<bool>(has_alpha_canal));
}

/**
 * @brief loads an OpenGL texture from the image at the given `path`
 * @param path the path to the image, from the executable
 * @param has_alpha_canal whether the image has an alpha canal or not
 */
void Texture::load(const char* path, bool && has_alpha_canal)
{
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

    stbi_image_free(img);
}

/**
 * @brief getter for the OpenGL texture object
 * @return unsigned int the id of the texture
 */
unsigned int Texture::get_id() const
{
    return texture;
}

/**
 * @brief activates the texture
 */
void Texture::activate(const Shader& shader)
{
    shader.set_uniform(
        std::string("texture" + std::to_string((int)(unit - GL_TEXTURE0))).c_str(),
        (int)(unit - GL_TEXTURE0)
    );

    glActiveTexture(unit);
    glBindTexture(GL_TEXTURE_2D, texture);
}

/**
 * @brief activates the texture
 */
void Texture::desactivate(const Shader& shader)
{
    glActiveTexture(unit);
    glBindTexture(GL_TEXTURE_2D, 0);
}


/**
 * @brief destroys the texture
 */
void Texture::destroy()
{
    glDeleteTextures(1, &texture);
}