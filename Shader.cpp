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
    set_uniform(MODEL.c_str(), model);
}

/**
 * @brief setter for the view matrix
 * @param model the view matrix
 */
void Shader::set_view(glm::mat4 view) const
{
    set_uniform(VIEW.c_str(), view);
}

/**
 * @brief setter for the projection matrix
 * @param model the projection matrix
 */
void Shader::set_projection(glm::mat4 projection) const
{
    set_uniform(PROJECTION.c_str(), projection);
}

/**
 * @brief setter for the model_normals matrix
 * @param model the model_normals matrix
 */
void Shader::set_model_normals(glm::mat3 model_normals) const
{
    set_uniform(MODEL_NORMALS.c_str(), model_normals);
}
