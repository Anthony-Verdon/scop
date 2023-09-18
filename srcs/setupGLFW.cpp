#include "main.hpp"

/**
 * callback function when the window is resized.
 * the viewport is the part of the window where we can draw
*/
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    (void)window;

    glViewport(0, 0, width, height);
}

/**
 * instantiate a window,
 * defined it as the current context
 * and set the framebuffer_size_callback() function
 * to the callback of the same name
*/
GLFWwindow* initWindow()
{
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return (NULL);
    }
    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    return (window);
}

/**
 * init GLFW to configure it,
 * tell it that we use version 3.3 and core-profile of OpenGL,
 * call initWindow(),
 * and initialize functions pointers for OpenGL
*/
GLFWwindow* initGLFW()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = initWindow();
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return (NULL);
    }

    return (window);
}