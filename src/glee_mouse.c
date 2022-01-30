#include "glee_common.h"

static double scroll_x = 0.0, scroll_y = 0.0;
static unsigned int mouse_state = GLFW_RELEASE;

void GLmouse_scroll(GLFWwindow* window, double xoffset, double yoffset)
{
    scroll_x = xoffset;
    scroll_y = yoffset;
}

void glee_mouse_pos(float* x, float* y)
{
    double dx, dy;
    int w, h;

    GLFWwindow* win = glee_window_get();
    glfwGetFramebufferSize(win, &w, &h);
    glfwGetCursorPos(win, &dx, &dy);
    
    *x = (float)dx;
    *y = (float)h - (float)dy;
}

void glee_mouse_pos_3d(float* x, float* y)
{
    double dx = (double)(*x), dy = (double)(*y);
    int w, h;

    GLFWwindow* win = glee_window_get();
    glfwGetFramebufferSize(win, &w, &h);
    glfwGetCursorPos(win, &dx, &dy);
    
    *x = ((float)w * 0.5f - (float)dx);
    *y = ((float)h * 0.5f - (float)dy);
}

void glee_mouse_scroll(float* x, float* y)
{
    static float dx = 0.0, dy = 0.0;
    
    *x = scroll_x - dx;
    *y = scroll_y - dy;
    
    dx = scroll_x;
    dy = scroll_y;
}

unsigned int glee_mouse_down(unsigned int button)
{
    return glfwGetMouseButton(glee_window_get(), button);
}

unsigned int glee_mouse_pressed(unsigned int button)
{
    unsigned int ret = 0;
    int mouse_button = glfwGetMouseButton(glee_window_get(), button);
    if (mouse_button == GLFW_PRESS && mouse_state == GLFW_RELEASE) ret = 1;
    mouse_state = mouse_button;
    return ret;
}

unsigned int glee_mouse_released(unsigned int button)
{
    return glfwGetMouseButton(glee_window_get(), button) == 0;
}

void glee_mouse_mode(unsigned int mouse_lock)
{
    GLFWwindow* win = glee_window_get();
    if (mouse_lock) glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    else glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}