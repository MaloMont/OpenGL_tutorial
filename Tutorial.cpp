#include "Tutorial.h"

Tutorial::Tutorial()
{
    init_libraries();

    shader.load(VERTEX_SHADER_FILE, FRAGMENT_SHADER_FILE);
}

Tutorial::~Tutorial()
{
    world.destroy();
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
    glm::vec3 cubePositions[10] = {
        glm::vec3( 0.0f,  0.0f,  0.0f), 
        glm::vec3( 2.0f,  5.0f, -15.0f), 
        glm::vec3(-1.5f, -2.2f, -2.5f),  
        glm::vec3(-3.8f, -2.0f, -12.3f),  
        glm::vec3( 2.4f, -0.4f, -3.5f),  
        glm::vec3(-1.7f,  3.0f, -7.5f),  
        glm::vec3( 1.3f, -2.0f, -2.5f),  
        glm::vec3( 1.5f,  2.0f, -2.5f), 
        glm::vec3( 1.5f,  0.2f, -1.5f), 
        glm::vec3(-1.3f,  1.0f, -1.5f)  
    };

    std::vector<Instance> my_cubes;

    for(auto && pos : cubePositions)
    {
        my_cubes.push_back(world.create(CUBE));
        my_cubes.back().pos = pos;
        my_cubes.back().rotation_axis = glm::vec3(glm::linearRand<float>(0.0f, 1.0f), glm::linearRand<float>(0.0f, 1.0f), glm::linearRand<float>(0.0f, 1.0f));
        my_cubes.back().rotation_angle = glm::linearRand<float>(0, M_PI_2);
    }

    bool rotates[10];
    for(int i = 0 ; i < 10 ; ++i)
        rotates[i] = (i % 3 == 0);

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

        for(int i = 0 ; i < 10 ; ++i)
        {
            if(rotates[i])
                my_cubes[i].rotation_angle = glm::radians((float)value);

            world.draw(shader, my_cubes[i]);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
