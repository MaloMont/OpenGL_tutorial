#include "Texture.h"

#include "debug_helper.h"


/**
 * @brief Construct an empty new Texture object
 */
Texture::Texture()
{
    loaded = false;
}

/**
 * @brief Constructs a new Texture object
 * @param diff_path the path of the diffuse texture
 * @param diff_has_alpha whether the diffuse texture has an alpha canal or not
 * @param spec_path the path of the specular texture
 * @param spec_has_alpha whether the specular texture has an alpha canal or not
 */
Texture::Texture(const char* diff_path, const bool diff_has_alpha, const char* spec_path, const bool spec_has_alpha)
{
    std::cout << "loading by Texture::Texture : " << diff_path << " and " << spec_path << std::endl;
    std::cout << diffuse_text << std::endl;
    partial_load(diffuse_text, diff_path, diff_has_alpha);
    std::cout << "became: " << diffuse_text << std::endl;
    partial_load(specular_text, spec_path, spec_has_alpha);
    loaded = true;
}

/**
 * @brief Constructs a new Texture object
 * @param spec a Texture_spec struct defining the specificities of the texture
 */
Texture::Texture(Texture_spec spec) : Texture(spec.diff_path, spec.diff_has_alpha, spec.spec_path, spec.spec_has_alpha)
{   }

/**
 * @brief Destroys the Texture object
 */
Texture::~Texture()
{
    destroy();
}

/**
 * @brief loads a texture from the files of the images
 * @param diff_path the path to the diffuse texture
 * @param diff_has_alpha true if the diffuse texture has an alpha canal
 * @param spec_path the path to the specular texture
 * @param spec_has_alpha true if the specular texture has an alpha canal
 */
void Texture::load(const char* diff_path, const bool diff_has_alpha, const char* spec_path, const bool spec_has_alpha)
{
    std::cout << "loading by Texture::load : " << diff_path << " and " << spec_path << std::endl;
    destroy();
    partial_load(diffuse_text, diff_path, diff_has_alpha);
    partial_load(specular_text, spec_path, spec_has_alpha);
    loaded = true;
}

/**
 * @brief loads a texture from a Texture_spec struct
 * @param spec the struct defining the texture properties
 */
void Texture::load(Texture_spec spec)
{
    load(spec.diff_path, spec.diff_has_alpha, spec.spec_path, spec.spec_has_alpha);
}

/**
 * @brief loads an OpenGL texture from the image at the given `path`
 * @param texture the texture's future emplacement : either diffuse_text or specular_text
 * @param path the path to the image, from the executable
 * @param has_alpha_canal whether the image has an alpha canal or not
 */
void Texture::partial_load(unsigned int& texture, const char* path, const bool has_alpha_canal)
{
    std::cout << "loading from file : " << path << std::endl;
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

    std::cout << "generated texture id : " << texture << "\n";

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

//    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(img);
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

    loaded = false;
}

/**
 * @brief getter for the shininess param of the texture
 */
float Texture::get_shininess() const
{
    return shininess;
}
