#include "glee_common.h"
#include <stdio.h>

/*
-------------
 -> window <- 
-------------
*/

static void GLwindow_size(GLFWwindow* window, int width, int height)
{
    glee.width = width;
    glee.height = height;
    glee.update = 1;
}

static void GLframebuffer_size(GLFWwindow* window, int width, int height)
{
    glee.update = 1;
}

GLFWwindow* glee_window_get()
{
    return glee.window;
}

void glee_window_create(const char* title, int width, int height, unsigned int fullscreen, unsigned int resizable)
{
    GLFWwindow* window;

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
        glee.width = mode->width;
        glee.height = mode->height;
    } else {
        window = glfwCreateWindow(width, height, title, NULL, NULL);
        glee.width = width;
        glee.height = height;
    }

    if (window == NULL) {
        printf("Window failed to create\n");
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glfwSetWindowAspectRatio(window, width, height);
    glfwSetWindowSizeLimits(window, width / 2, height / 2, GLFW_DONT_CARE, GLFW_DONT_CARE);
    glfwSetWindowSizeCallback(window, GLwindow_size);
    glfwSetFramebufferSizeCallback(window, GLframebuffer_size);
    glfwSetDropCallback(window, GLdrop_file);
    
    glfwSetInputMode(window, GLFW_LOCK_KEY_MODS, GLFW_TRUE);
    glfwSetKeyCallback(window, GLkeyboard);
    glfwSetScrollCallback(window, GLmouse_scroll);

#ifndef __APPLE__
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        printf("GLEW Library failed to initialize.\n");
        return;
    }
#endif

    glEnable(GL_MULTISAMPLE);
    glEnable(GL_BLEND); 
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthFunc(GL_LESS);

    glee.window = window;
    glee.fullscreen = fullscreen;
    printf("Core initiated succesfully.\n");
}

void glee_window_set_size(int width, int height)
{
    glfwSetWindowSize(glee.window, width, height);
    glee.update = 1;
}

void glee_window_get_size(int* width, int* height)
{
    glfwGetWindowSize(glee.window, width, height);
}

void glee_window_set_position(int x, int y)
{
    glfwSetWindowPos(glee.window, x, y);
}

void glee_window_get_position(int* x, int* y)
{
    glfwGetWindowPos(glee.window, x, y);
}

unsigned int glee_window_is_open()
{
    return !glfwWindowShouldClose(glee.window);
}
