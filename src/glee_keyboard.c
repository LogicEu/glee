#include "glee_common.h"

#ifndef __APPLE__ 
    #define GLFW_MOD_CAPS_LOCK 0x0010
#endif

static unsigned int keys[1024], pressed_keys[1024], char_ret = 1;
static char key_char = '\0';

void GLkeyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key < 128 && !keys[key]) {
        if (mods == GLFW_MOD_CAPS_LOCK || mods == GLFW_MOD_SHIFT || key < 65) key_char = key;
        else key_char = key + 32;
        char_ret = 1;
    } 
    
    keys[key] = action;
    pressed_keys[key] = pressed_keys[key] * (action != 0);
}

unsigned int glee_key_down(unsigned int k)
{
    return keys[k];
}

unsigned int glee_key_pressed(unsigned int k)
{
    if (!pressed_keys[k] && keys[k]) {
        pressed_keys[k] = 1;
        return 1;
    }
    return 0;
}

unsigned int glee_key_released(unsigned int k)
{
    if (!keys[k] && pressed_keys[k]) {
        pressed_keys[k] = 0;
        return 1;
    }
    return 0;
}

char glee_key_char()
{
    char ret = '\0';
    if (char_ret) {
        ret = key_char;
        char_ret = 0;
    }
    return ret;
}
