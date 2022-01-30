#include <glee.h>

float glee_time_get()
{
    return (float)glfwGetTime();
}

float glee_time_delta(float* last_time)
{
    float current_time = glfwGetTime();
    float delta_time = current_time - *last_time;
    *last_time = current_time;
    return delta_time;
}