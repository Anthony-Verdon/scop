#ifndef INIT_HPP
#define INIT_HPP

#include <GLFW/glfw3.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void initGLFW();
void initOpenGL();
GLFWwindow *initWindow();

#endif