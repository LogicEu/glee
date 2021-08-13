#include <glee.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned new_file = 0;
static unsigned int used = 0;
static char file_paths[16][256];

/*
-------------
 -> files <- 
-------------
*/

void GLdrop_file(GLFWwindow* window, int count, const char** paths)
{
    if (used >= 16) return;
    for (int i = 0; i < count; i++) {
        strcpy(file_paths[used++], paths[i]);
        if (used == 15) break;
    }
    new_file = 1;
}

char* glee_file_read(const char* path)
{
    FILE* file = fopen(path, "rb");
    if (!file) {
        printf("Cannot open file '%s'\n", path);
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char* ret = (char*)malloc(sizeof(length + 1));
    fread(ret, length, 1, file);
    ret[length] = '\0';
    fclose(file);
    return ret;
}

unsigned int glee_window_file_check()
{
    return used;
}

char* glee_window_file_get()
{
    if (used) return file_paths[--used];
    return NULL;
}
