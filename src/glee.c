#include "glee_common.h"
#include <stdio.h>

void glee_init()
{
    if (!glfwInit()) {
        printf("glee failed to initiate GLFW\n");
        return;
    }
}

void glee_deinit()
{
    glfwDestroyWindow(glee_window_get());
    glfwTerminate();
}

void glee_mode_set(int mode)
{
    if (mode) {
        glEnable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
    } else {
        glDisable(GL_CULL_FACE);
        glDisable(GL_DEPTH_TEST);
    }
}
