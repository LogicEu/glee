#include "glee_common.h"

void glee_screen_color(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
}

void glee_screen_clear(int mode)
{   
    if (mode == GLEE_MODE_2D) glClear(GL_COLOR_BUFFER_BIT);
    else if (mode == GLEE_MODE_3D) glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    else if (mode == GLEE_MODE_FULL) glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void glee_screen_refresh()
{
    glfwSwapBuffers(glee_window_get());
    glfwPollEvents();
}