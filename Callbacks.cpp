#include "Callbacks.h"

/**
 * @brief called by glfw when the window is resized
 * @param window the window this callback will be linked to
 * @param width new width
 * @param height new height
 */
void Callbacks::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
