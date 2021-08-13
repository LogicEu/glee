#include "glee_common.h"

/*
-------------
 -> screen <- 
-------------
*/

void glee_screen_color(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
}

void glee_screen_clear()
{   
    if (glee.mode) glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    else glClear(GL_COLOR_BUFFER_BIT);
}

void glee_screen_refresh()
{
    glfwSwapBuffers(glee.window);
    glfwPollEvents();
}