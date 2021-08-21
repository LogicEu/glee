#ifndef GLEE_COMMON_H
#define GLEE_COMMON_H

#include <glee.h>

typedef struct gleeManager {
    GLFWwindow* window;
    unsigned int width;
    unsigned int height;
    unsigned int scale;
    unsigned int fullscreen;
    unsigned int mode;
    unsigned int mouse_lock;
    unsigned int update;
} gleeManager;

extern gleeManager glee;

void GLmouse_scroll(GLFWwindow* window, double xoffset, double yoffset);
void GLkeyboard(GLFWwindow* window, int key, int scancode, int action, int mods);
void GLdrop_file(GLFWwindow* windwo, int count, const char** paths);

#endif