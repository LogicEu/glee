#include "glee_common.h"
#include <stdio.h>

#ifndef __APPLE__
    #define GLFW_LOCK_KEY_MODS 0x00033004
#endif

/*
-------------
 -> window <- 
-------------
*/

static GLFWwindow* window;

GLFWwindow* glee_window_get()
{
    return window;
}

void glee_window_create(const char* title, int width, int height, unsigned int fullscreen, unsigned int resizable)
{
#ifdef __APPLE__
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);    
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_COCOA_GRAPHICS_SWITCHING, GLFW_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_RESIZABLE, resizable);
#endif

    if (fullscreen) {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        glfwWindowHint(GLFW_RED_BITS, mode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
        window = glfwCreateWindow(mode->width, mode->height, title, monitor, NULL);
    } else {
        window = glfwCreateWindow(width, height, title, NULL, NULL);
    }

    if (window == NULL) {
        printf("glee failed to initiate a GLFW window\n");
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glfwSetWindowAspectRatio(window, width, height);
    glfwSetWindowSizeLimits(window, width / 2, height / 2, GLFW_DONT_CARE, GLFW_DONT_CARE);
    //glfwSetWindowSizeCallback(window, GLwindow_size);
    //glfwSetFramebufferSizeCallback(window, GLframebuffer_size);
    glfwSetDropCallback(window, GLdrop_file);
    
    glfwSetInputMode(window, GLFW_LOCK_KEY_MODS, GLFW_TRUE);
    glfwSetKeyCallback(window, GLkeyboard);
    glfwSetScrollCallback(window, GLmouse_scroll);

#ifndef __APPLE__
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        printf("glee failed to initiate GLEW\n");
        return;
    }
#endif

    glEnable(GL_MULTISAMPLE);
    glEnable(GL_BLEND); 
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthFunc(GL_LESS);
}

void glee_window_set_size(int width, int height)
{
    glfwSetWindowSize(window, width, height);
}

void glee_window_get_size(int* width, int* height)
{
    glfwGetWindowSize(window, width, height);
}

void glee_window_get_framebuffer_size(int* width, int* height)
{
    glfwGetFramebufferSize(window, width, height);
}

void glee_window_set_position(int x, int y)
{
    glfwSetWindowPos(window, x, y);
}

void glee_window_get_position(int* x, int* y)
{
    glfwGetWindowPos(window, x, y);
}

unsigned int glee_window_is_open()
{
    return !glfwWindowShouldClose(window);
}
