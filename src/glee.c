#include "glee_common.h"
#include <stdio.h>

/*
-----------
 -> glee <- 
-----------
*/

gleeManager glee;

void glee_init()
{
    if (!glfwInit()) {
        printf("glee failed to initiate GLFW\n");
        return;
    }
    glee.window = NULL;
    glee.width = 800;
    glee.height = 600;
    glee.scale = 1;
    glee.fullscreen = 0;
    glee.mode = 0;
    glee.mouse_lock = 0;
    glee.update = 0;
}

void glee_deinit()
{
    glfwTerminate();
}

void glee_set_2d_scale(unsigned int scale)
{
    glee.scale = scale + (scale == 0);
}

unsigned int glee_get_2d_scale()
{
    return glee.scale;
}

void glee_get_size(unsigned int* width, unsigned int* height)
{
    *width = glee.width;
    *height = glee.height;
}

void glee_set_3d_mode()
{
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glee.mode = 1;
}

void glee_set_2d_mode()
{
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glee.mode = 0;
}
