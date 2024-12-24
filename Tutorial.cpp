#include "Tutorial.h"

Tutorial::Tutorial()
{
    init_libraries();

    shader.load(VERTEX_SHADER_FILE, FRAGMENT_SHADER_FILE);

    cube_template.init();

    cube_template.add_texture("../assets/textures/container.jpg", false);
    cube_template.add_texture("../assets/textures/awesomeface.png", true);
}

Tutorial::~Tutorial()
{
    cube_template.destroy();
    glfwTerminate();
}

/**
 * @brief initializes glfw 3.3 with OpenGL core profile, and creates an OpenGL context. If one fails, the app stops.
 */
void Tutorial::init_glfw()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    std::string wTitle = "LearnOpenGL, v" + std::to_string(VERSION_MAJOR)
                                    + "." + std::to_string(VERSION_MINOR);
    window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, wTitle.c_str(), NULL, NULL);
    if (window == NULL)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window);
}

/**
 * @brief initializes glad
 */
void Tutorial::init_glad()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        exit(-1);
    }
}

/**
 * @brief configures both glfw and glad
 */
void Tutorial::init_libraries()
{
    init_glfw();
    init_glad();

    glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);
    glfwSetFramebufferSizeCallback(window, Callbacks::framebuffer_size_callback);
}

/**
 * @brief call functions corresponding to the current events state
 */
void Tutorial::process_input()
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

/**
 * @brief app body : one loop corresponds to one app frame
 */
void Tutorial::render_loop()
{
    auto my_cube = cube_template.create_instance();

    shader.turn_on();

    glEnable(GL_DEPTH_TEST);

    int value = 0;
    while(not glfwWindowShouldClose(window))
    {
        value += 1;
        process_input();

        // rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = glm::mat4(1.0f);
        // note that we're translating the scene in the reverse direction of where we want to move
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); 
        shader.set_uniform("view", view);

        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.0f), (float)WIN_WIDTH / (float)WIN_HEIGHT, 0.1f, 100.0f);
        shader.set_uniform("projection", projection);

        cube_template.set_instance_rotation_angle(my_cube, glm::radians((float)value));
        cube_template.set_instance_rotation_axis(my_cube,
            glm::vec3(sin(glm::radians((float)value)) + 1.0f,
                      sin(glm::radians((float)value)) + 1.0f,
                      sin(glm::radians((float)value)) + 1.01f // to prevent [axis = (0, 0, 0)]
                     ));

        cube_template.draw(shader, my_cube);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
