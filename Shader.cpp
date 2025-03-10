#include "Shader.h"

Shader::Shader()
{  }

/**
 * @brief compiles the shader
 * @param vertex_path the path to the vertext shader
 * @param fragment_path the path to the fragment shader
 * @return true if successful
 * @return false if not
 */
bool Shader::load(std::string vertex_path, std::string fragment_path, std::string _name)
{
    unsigned int vertexShader;
    unsigned int fragmentShader;

// TODO: remove exits

    if(not compile_vertexShader(vertexShader, vertex_path))
    {
        exit(EXIT_FAILURE);
        return false;
    }

    if(not compile_fragmentShader(fragmentShader, fragment_path))
    {
        glDeleteShader(vertexShader);
        exit(EXIT_FAILURE);
        return false;
    }

    if(not link_shaderProgram(vertexShader, fragmentShader))
    {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        exit(EXIT_FAILURE);
        return false;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    name = _name;
    
    loaded = true;

    return true;
}

/**
 * @brief Get the content of the file at `path`
 * @param path the path to the file from executable directory
 * @return std::string the content of the file
 */
std::string get_file_content(std::string path)
{
    std::string content;
    std::ifstream file;

    try 
    {
        file.open(path);

        std::stringstream ss;
        ss << file.rdbuf();		
        content = ss.str();		

        file.close();
    }
    catch(std::ifstream::failure & e)
    {
        std::cerr << "[ERROR]: Shader::get_file_content => FILE_NOT_SUCCESFULLY_READ => path: " << path << std::endl;
    }

    return content;
}

/**
 * @brief compiles the vertexShader from the sources vertexShaderSource
 * @param vertexShader a pointer to the vertex shader object
 */
bool Shader::compile_vertexShader(unsigned int& vertexShader, std::string vertex_path)
{
    std::string s = get_file_content(vertex_path);
    const char* vertexShaderSource = s.c_str();

    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(not success)
    {
        char infoLog[1024];
        glGetShaderInfoLog(vertexShader, 1024, NULL, infoLog);
        std::cerr << "[ERROR]: Shader::compile_vertexShader => COMPILATION_FAILED.\n"
                  << "shader file : " << vertex_path << "\n"
                  << infoLog << std::endl;
        return false;
    }
    return true;
}

/**
 * @brief compiles the fragmentShader from the sources fragmentShaderSource
 * @param fragmentShader a pointer to the fragment shader object
 */
bool Shader::compile_fragmentShader(unsigned int& fragmentShader, std::string fragment_path)
{
    std::string s = get_file_content(fragment_path);
    const char* fragmentShaderSource = s.c_str();

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    int success;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if(not success)
    {
        char infoLog[1024];
        glGetShaderInfoLog(fragmentShader, 1024, NULL, infoLog);
        std::cerr << "[ERROR]: Shader::compile_fragmentShader => COMPILATION FAILED.\n"
                  << "shader file : " << fragment_path << "\n"
                  << infoLog << std::endl;
        return false;
    }
    return true;
}

/**
 * @brief links both shaders to create the final one
 * @param vertexShader the vertex shader pointer
 * @param fragmentShader the fragment shader pointer
 */
bool Shader::link_shaderProgram(unsigned int& vertexShader, unsigned int& fragmentShader)
{
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if(not success) {
        char infoLog[1024];
        glGetProgramInfoLog(shaderProgram, 1024, NULL, infoLog);
        std::cerr << "[ERROR]: Shader::link_shaderProgram => LINKING FAILED.\n" << infoLog << std::endl;
        return false;
    }
    return true;
}

void Shader::destroy()
{
    loaded = false;
    /* TODO */
}

bool Shader::is_loaded() const
{
    return loaded;
}

/**
 * @brief define this shader as the one in use
 */
void Shader::turn_on() const
{
    if(not loaded)
    {
        std::cerr << "[ERROR]: Shader not loaded.\n";
        return;
    }

    glUseProgram(shaderProgram);
}

/**
 * @brief returns the location of the given uniform
 * @param uniform_name the name of the uniform
 * @return (unsigned int) the location of the uniform
 */
unsigned int Shader::get_location(const char* uniform_name) const
{
    int location = glGetUniformLocation(shaderProgram, uniform_name);
    if(location < 0)
        std::cerr << "[WARNING]: (in shader " << name << ") : couldn't find uniform location for \'" << uniform_name << "\'" << std::endl;

    return location;
}

/**
 * @brief sets a vec4 uniform in a shader program to the given value
 * /!\ turns the shader on
 * @param uniform_name name of the uniform in the shader program
 * @param x x value of the uniform
 * @param y y value of the uniform
 * @param z z value of the uniform
 * @param w w value of the uniform
 */
void Shader::set_uniform(const char* uniform_name, float x, float y, float z, float w) const
{
    unsigned int location = get_location(uniform_name);
    turn_on();
    glUniform4f(location, x, y, z, w);
}

/**
 * @brief sets a bool uniform in a shader program to the given `value`
 * /!\ turns the shader on
 * @param uniform_name name of the uniform in the shader program
 * @param value value of the uniform
 */
void Shader::set_uniform(const char* uniform_name, bool value) const
{         
    unsigned int location = get_location(uniform_name);
    turn_on();
    glUniform1i(location, (int)value);
}

/**
 * @brief sets a int uniform in a shader program to the given `value`
 * /!\ turns the shader on
 * @param uniform_name name of the uniform in the shader program
 * @param value value of the uniform
 */
void Shader::set_uniform(const char* uniform_name, int value) const
{
    unsigned int location = get_location(uniform_name);
    turn_on();
    glUniform1i(location, value);
}

/**
 * @brief sets a float uniform in a shader program to the given `value`
 * /!\ turns the shader on
 * @param uniform_name name of the uniform in the shader program
 * @param value value of the uniform
 */
void Shader::set_uniform(const char* uniform_name, float value) const
{ 
    unsigned int location = get_location(uniform_name);
    turn_on();
    glUniform1f(location, value);
}

/**
 * @brief sets a mat4 uniform in a shader program to the given `matrix`
 * @param uniform_name name of the uniform in the shader program
 * @param matrix the matrix
 */
void Shader::set_uniform(const char* uniform_name, glm::mat4 matrix) const
{
    unsigned int location = get_location(uniform_name);
    turn_on();
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

/**
 * @brief sets a mat4 uniform in a shader program to the given `matrix`
 * @param uniform_name name of the uniform in the shader program
 * @param matrix the matrix
 */
void Shader::set_uniform(const char* uniform_name, glm::mat3 matrix) const
{
    unsigned int location = get_location(uniform_name);
    turn_on();
    glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

/**
 * @brief sets a vec3 uniform in a shader program to the given `vec`
 * @param uniform_name name of the uniform in the shader program
 * @param vec the vec3
 */
void Shader::set_uniform(const char* uniform_name, glm::vec3 vec) const
{
    unsigned int location = get_location(uniform_name);
    turn_on();
    glUniform3fv(location, 1, glm::value_ptr(vec));
}

/**
 * @brief setter for the model matrix
 * @param model the model matrix
 */
void Shader::set_model(glm::mat4 model) const
{
    set_uniform(MODEL, model);
}

/**
 * @brief setter for the view matrix
 * @param model the view matrix
 */
void Shader::set_view(glm::mat4 view) const
{
    set_uniform(VIEW, view);
}

/**
 * @brief setter for the projection matrix
 * @param model the projection matrix
 */
void Shader::set_projection(glm::mat4 projection) const
{
    set_uniform(PROJECTION, projection);
}

/**
 * @brief setter for the model_normals matrix
 * @param model the model_normals matrix
 */
void Shader::set_model_normals(glm::mat3 model_normals) const
{
    set_uniform(MODEL_NORMALS, model_normals);
}

/**
 * @brief activates the given texture
 * @param texture the texture to activate
 */
void Shader::activate(ressources::ID id) const
{
    set_uniform(MATERIAL_DIFFUSE_MAP, DIFFUSE_UNIT);
    set_uniform(MATERIAL_SPECULAR_MAP, SPECULAR_UNIT);

    ressources::activate(id, GL_TEXTURE0 + DIFFUSE_UNIT, GL_TEXTURE0 + SPECULAR_UNIT);
    set_uniform(MATERIAL_SHININESS, ressources::get_shininess(id));
}

/**
 * @brief desactivates the given texture
 * @param texture the texture to desactivate
 */
void Shader::desactivate(ressources::ID id) const
{
    ressources::desactivate(id);
    set_uniform(MATERIAL_SHININESS, (float)0.0);
}

void Shader::apply_param(std::string PARAM, auto param, int iLight) const
{
    std::string param_name;
    for(int i = 0 ; i < PARAM.size() ; ++i)
    {
        if(PARAM[i] == '.' and PARAM[i - 1] == 't')
            param_name += "[" + std::to_string(iLight) + "].";
        else
            param_name += PARAM[i];
    }

    set_uniform(param_name.c_str(), param);
}

void Shader::set_light(glm::vec3 pos, Light_spec spec, int iLight) const
{
    apply_param(LIGHT_POS, pos, iLight);

    apply_param(LIGHT_AMBIENT, spec.ambient, iLight);
    apply_param(LIGHT_DIFFUSE, spec.diffuse, iLight);
    apply_param(LIGHT_SPECULAR, spec.specular, iLight);

    if(name == SHADER_NAME[OBJ_SHADER])
    {
        apply_param(LIGHT_IS_AT_INFINITY, spec.is_at_infinity, iLight);
        apply_param(LIGHT_DIRECTION, spec.direction, iLight);

        apply_param(LIGHT_IS_SPOTLIGHT, spec.is_spotlight, iLight);
        apply_param(LIGHT_INNER_CUTOFF, spec.inner_cutoff, iLight);
        apply_param(LIGHT_OUTER_CUTOFF, spec.outer_cutoff, iLight);

        apply_param(LIGHT_ATTENUATION_CST, spec.attenuation.constant, iLight);
        apply_param(LIGHT_ATTENUATION_LIN, spec.attenuation.linear, iLight);
        apply_param(LIGHT_ATTENUATION_QUD, spec.attenuation.quadratic, iLight);
    }
}

void Shader::set_view_pos(glm::vec3 view_pos) const
{
    set_uniform(VIEW_POS, view_pos);
}

