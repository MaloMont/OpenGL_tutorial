#include "Cube.h"

/**
 * @brief Construct a new Cube object by initializing the VBO, the VAO and the EBO
 */
Cube::Cube(bool && delay_init /* = false */)
{
    if(not delay_init)
        init();
}

/**
 * @brief initializes the VBO, the VAO, abd buffers the vertices
 */
void Cube::init()
{
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);  
    buffer();

    add_texture("../assets/textures/container.jpg", false);
    add_texture("../assets/textures/awesomeface.png", true);

    loaded = true;
}

/**
 * @brief Destroy the Cube object by freeing its VAO, its VBO and its EBO (only if the cube is loaded)
 */
Cube::~Cube()
{
    if(loaded)
        destroy();
}

/**
 * @brief frees the allocated datas
 */
void Cube::destroy()
{
    if(not loaded)
        return;

    loaded = false;
    remove_all_texture();
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

/**
 * @brief changes the vertices of the triangle.
 * @param new_vertices the 4 new vertices. Has to be of format
 * posX, posY, posZ, colorR, colorG, colorB, textS, testT
 * for each of the 4 vertices
 */
void Cube::set(float new_vertices[NB_VERTICES])
{
    if(new_vertices != NULL)
        for(int i = 0 ; i < NB_VERTICES ; ++i)
            vertices[i] = new_vertices[i];

    buffer();
}

/**
 * @brief buffers the vertices into the curently bound VBO in static mod
 */
void Cube::buffer()
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
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, NB_DATA_PER_VERTICE * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // same for texture coordinates
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, NB_DATA_PER_VERTICE * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


/**
 * @brief draw cube vertex 
 * 
 * @param to_draw the parameters of the instance to draw (eg world position, shader, ...)
 */
void Cube::draw(const Instance& to_draw)
{
    for(auto && text : textures)
        text.activate(to_draw.shader);

    glBindVertexArray(VAO);

    to_draw.shader.set_model(to_draw.get_model_mat4());

    glDrawArrays(GL_TRIANGLES, 0, NB_TO_DRAW);

    glBindVertexArray(0);

    for(auto && text : textures)
        text.desactivate(to_draw.shader);
}

/**
 * @brief frees every texture the object has
 */
void Cube::remove_all_texture()
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
void Cube::set_textures(std::vector<Texture> _textures)
{
    remove_all_texture();
    for(auto && cur_texture : _textures)
        bind_texture(cur_texture);
}

/**
 * @brief bind one texture to the object. The texture is independent from the object and will not be destroyed by this object's destructor.
 * @param _texture the texture object tobe added
 */
void Cube::bind_texture(Texture _texture)
{
    textures.push_back(_texture);
    texture_is_mine.push_back(false);
}

/**
 * @brief creates a new texture specific to this object. When the object will be destroyed, the texture will also be destroyed.
 * @param _texture the texture object tobe added
 */
void Cube::add_texture(const char* path, bool && has_alpha_chanel)
{
    textures.push_back(Texture(GL_TEXTURE0 + textures.size(), path, std::forward<bool>(has_alpha_chanel)));
    texture_is_mine.push_back(true);
}
