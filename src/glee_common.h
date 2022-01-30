#ifndef GLEE_COMMON_H
#define GLEE_COMMON_H

#include <glee.h>

void GLmouse_scroll(GLFWwindow* window, double xoffset, double yoffset);
void GLkeyboard(GLFWwindow* window, int key, int scancode, int action, int mods);
void GLdrop_file(GLFWwindow* windwo, int count, const char** paths);

#endif