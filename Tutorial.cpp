#include "Tutorial.h"

Tutorial::Tutorial()
{
    init_libraries();
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
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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

    // DEBUG only
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(errorHandler, NULL);
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
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    if(first_mouse)
    {
        last_mouse_x = xpos;
        last_mouse_y = ypos;
        first_mouse = false;
    }
    float delta_x = xpos - last_mouse_x;
    float delta_y = last_mouse_y - ypos; // reversed since y-coordinates range from bottom to top
    last_mouse_x = xpos;
    last_mouse_y = ypos;
    camera.inc_angles(delta_x, delta_y);

    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.go_straight(delta_time);
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.go_back(delta_time);
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.go_left(delta_time);
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.go_right(delta_time);
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.set_target(glm::vec3(0.0f, 0.0f, 0.0f));
}


auto Tutorial::setup()
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

    std::vector<Cube::Instance> my_cubes;

    for(auto && pos : cubePositions)
    {
        my_cubes.push_back(world.create<Cube>(CUBE, OBJ_SHADER));
        my_cubes.back().pos = pos;
        my_cubes.back().rotation_axis = glm::vec3(glm::linearRand<float>(0.0f, 1.0f), glm::linearRand<float>(0.0f, 1.0f), glm::linearRand<float>(0.0f, 1.0f));
        my_cubes.back().rotation_angle = glm::linearRand<float>(0, M_PI_2);
    }

    return my_cubes;
}

/**
 * @brief app body : one loop corresponds to one app frame
 */
void Tutorial::render_loop()
{
    auto my_cubes = setup();

    auto my_light = world.create<Light>(LIGHT, LIGHT_SHADER);
    my_light.pos = glm::vec3(1.0f,  0.0f,  3.0f);
    my_light.scaling = glm::vec3(0.2f, 0.2f, 0.2f);
    my_light.set_spec(SPOT_LIGHT);
    my_light.iLight = 0;

    auto my_sun = world.create<Light>(LIGHT, LIGHT_SHADER);
    my_sun.pos = glm::vec3(0.0f,  10.0f,  -5.0f);
    my_sun.scaling = glm::vec3(0.2f, 0.2f, 0.2f);
    my_sun.set_spec(SUN_LIGHT);
    my_sun.spec.direction = my_sun.pos;
    my_sun.iLight = 1;

    auto my_torch = world.create<Light>(LIGHT, LIGHT_SHADER);
    my_torch.scaling = glm::vec3(0.0001f, 0.0001f, 0.0001f);
    my_torch.set_spec(SPOT_LIGHT);
    my_torch.iLight = 2;

    bool rotates[10];
    for(int i = 0 ; i < 10 ; ++i)
        rotates[i] = (i % 3 == 0);

    glEnable(GL_DEPTH_TEST);

    float last_frame = glfwGetTime(); // Time of last frame

    while(not glfwWindowShouldClose(window))
    {
        float current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;

        process_input();

        // rendering
        glClearColor(0.05f, 0.05f, 0.07f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//        my_light.pos = glm::vec3(5.0f * cos(glm::radians((float)glfwGetTime() * 50.0f)), 0.0f, 5.0f * sin(glm::radians((float)glfwGetTime() * 50.0f)));

        my_torch.pos = camera.get_pos();
        my_torch.spec.direction = camera.get_direction();

        world.draw(my_light);
        world.draw(my_sun);
        world.draw(my_torch);

        world.update_light_conf(my_light.pos, my_light.get_spec(), my_light.iLight);
        world.update_light_conf(my_sun.pos,   my_sun.get_spec(), my_sun.iLight);
        world.update_light_conf(my_torch.pos, my_torch.get_spec(), my_torch.iLight);

        world.update_view_pos(camera.get_pos());
        world.update_shaders(camera.get_view(), camera.get_projection());

        for(int i = 0 ; i < 10 ; ++i)
        {
            if(rotates[i])
                my_cubes[i].rotation_angle = glm::radians((float)glfwGetTime() * 10.0f);

            world.draw(my_cubes[i]);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
