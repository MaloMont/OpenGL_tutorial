#include "Tutorial.h"

Tutorial::Tutorial()
{
    init_libraries();
    shader.load(VERTEX_SHADER_FILE, FRAGMENT_SHADER_FILE);
}

Tutorial::~Tutorial()
{
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
    Triangle my_triangle;
    my_triangle.add_texture("../assets/textures/container.jpg", false);
    my_triangle.add_texture("../assets/textures/awesomeface.png", true);

    shader.turn_on();

    int value = 0;
    while(not glfwWindowShouldClose(window))
    {
        value = value + 5;
        process_input();

        // rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        my_triangle.draw(shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
