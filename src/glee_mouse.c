#include "glee_common.h"

static double scroll_x = 0, scroll_y = 0;
static unsigned int mouse_state = GLFW_RELEASE;

/*
------------------
 -> mouse input <- 
------------------
*/

void GLmouse_scroll(GLFWwindow* window, double xoffset, double yoffset)
{
    scroll_x = xoffset;
    scroll_y = yoffset;
}

void glee_mouse_pos(float* x, float* y)
{
    double dx, dy;
    glfwGetCursorPos(glee.window, &dx, &dy);
    *x = (float)dx / glee.scale;
    *y = (glee.height - (float)dy) / glee.scale;
}

void glee_mouse_pos_3d(float* x, float* y)
{
    double dx = (double)(*x), dy = (double)(*y);
    glfwGetCursorPos(glee.window, &dx, &dy);
    *x = (glee.width * 0.5f - (float)dx);
    *y = (glee.height * 0.5f - (float)dy);
}

void glee_mouse_scroll(float* x, float* y)
{
    *x = scroll_x;
    *y = scroll_y;
}

unsigned int glee_mouse_down(unsigned int button)
{
    return glfwGetMouseButton(glee.window, button);
}

unsigned int glee_mouse_pressed(unsigned int button)
{
    unsigned int ret = 0;
    int mouse_button = glfwGetMouseButton(glee.window, button);
    if (mouse_button == GLFW_PRESS && mouse_state == GLFW_RELEASE) ret = 1;
    mouse_state = mouse_button;
    return ret;
}

unsigned int glee_mouse_released(unsigned int button)
{
    return glfwGetMouseButton(glee.window, button) == 0;
}

void glee_mouse_mode(unsigned int mouse_lock)
{
    if (mouse_lock) glfwSetInputMode(glee.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    else glfwSetInputMode(glee.window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}