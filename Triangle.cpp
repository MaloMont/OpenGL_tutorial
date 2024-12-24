#include "Triangle.h"

/**
 * @brief Construct a new Triangle object by initializing the VBO, the VAO and the EBO
 */
Triangle::Triangle()
{
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);  
    glGenBuffers(1, &EBO);
    buffer();
}

/**
 * @brief Destroy the Triangle object by freeing its VAO, its VBO and its EBO
 */
Triangle::~Triangle()
{
    remove_all_texture();
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

/**
 * @brief changes the vertices of the triangle.
 * @param new_vertices the 4 new vertices. Has to be of format
 * posX, posY, posZ, colorR, colorG, colorB, textS, testT
 * for each of the 4 vertices
 */
void Triangle::set(float new_vertices[NB_VERTICES])
{
    if(new_vertices != NULL)
        for(int i = 0 ; i < NB_VERTICES ; ++i)
            vertices[i] = new_vertices[i];

    buffer();
}

/**
 * @brief buffers the vertices into the curently bound VBO in static mod
 */
void Triangle::buffer()
{
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

        // vertices --> VBO ; remembered by the VAO
        // GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times.
        // GL_STATIC_DRAW: the data is set only once and used many times.
        // GL_DYNAMIC_DRAW: the data is changed a lot and used many times.
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // how datas are organised
        // first argument is cuz : layout (position = 0)
        // second argument cuz we deal with vec3
        // third cuz vec3 have float values
        // fourth : coordinates are NOT normalized
        // fifth : size between two consecutive vec3 begining (here we have only one vec3 (the color of the vertice) between two beginings)
        // sixth : data offset
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // same for colors => offest of 3 floats
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // same for texture coordinates
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        // order to draw vertices --> EBO ; remembered by the VAO
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Triangle::draw(const Shader& shader)
{
    for(auto && text : textures)
        text.activate(shader);

    glBindVertexArray(VAO);

    // 3 vertices in a triangle
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);//<-- tester la valeur '6'

    glBindVertexArray(0);

    for(auto && text : textures)
        text.desactivate(shader);
}


/**
 * @brief frees every texture the object has
 */
void Triangle::remove_all_texture()
{
    while(not textures.empty())
    {
        if(texture_is_mine.back())
            textures.back().destroy();

        textures.pop_back();
        texture_is_mine.pop_back();
    }
}

/**
 * @brief replaces the current textures with the ones in the `_texture` vector.
 * Those textures are independent from the object and will not be destroyed by this object's destructor.
 * @param _textures the new textures
 */
void Triangle::set_textures(std::vector<Texture> _textures)
{
    remove_all_texture();
    for(auto && cur_texture : _textures)
        bind_texture(cur_texture);
}

/**
 * @brief bind one texture to the object. The texture is independent from the object and will not be destroyed by this object's destructor.
 * @param _texture the texture object tobe added
 */
void Triangle::bind_texture(Texture _texture)
{
    textures.push_back(_texture);
    texture_is_mine.push_back(false);
}

/**
 * @brief creates a new texture specific to this object. When the object will be destroyed, the texture will also be destroyed.
 * @param _texture the texture object tobe added
 */
void Triangle::add_texture(const char* path, bool has_alpha_chanel)
{
    textures.push_back(Texture(GL_TEXTURE0 + textures.size(), path, has_alpha_chanel));
    texture_is_mine.push_back(true);
}
