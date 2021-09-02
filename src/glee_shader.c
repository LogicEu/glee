#include "glee_common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef __APPLE__
static const char* glsl_version = "#version 300 es\nprecision mediump float;\n\n";
#else
static const char* glsl_version = "#version 330 core\n\n";
#endif

/*
--------------
 -> shaders <- 
--------------
*/

char* glee_shader_file_read(const char* path)
{
    FILE* file = fopen(path, "rb");
    if (!file) {
        printf("glee could not open GLSL shader source file '%s'\n", path);
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    size_t pre_size = strlen(glsl_version);
    char* buffer = (char*)malloc(length + pre_size + 1);
    sprintf(&buffer[0], "%s", glsl_version);
    fread(&buffer[pre_size], 1, length, file);
    buffer[pre_size + length] = '\0';
    fclose(file);
    return buffer;
}

void glee_shader_compile(const GLchar* buffer, unsigned int shader)
{
    glShaderSource(shader, 1, &buffer, NULL);
    glCompileShader(shader);
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n %s", infoLog);
        printf("Shader asset:\n '%s\n'", buffer);
    }
}

void glee_shader_link(GLuint shader, unsigned int vshader, unsigned int fshader)
{
    int success;
    char infoLog[512];
    glAttachShader(shader, vshader);
    glAttachShader(shader, fshader);
    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader, 512, NULL, infoLog);
        printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n %s", infoLog);
    }
    glDeleteShader(vshader);
    glDeleteShader(fshader);
}

unsigned int glee_shader_load(const char *vpath, const char *fpath)
{
    unsigned int shader = glCreateProgram();

    char* vb = glee_shader_file_read(vpath);
    char* fb = glee_shader_file_read(fpath);
    if (!vb || !fb) {
        printf("glee had a problem loading shaders '%s' and '%s'\n", vpath, fpath);
        return 0;
    } else printf("glee is loading shaders '%s' and '%s'\n", vpath, fpath);

    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    
    glee_shader_compile(vb, vertex_shader);
    glee_shader_compile(fb, fragment_shader);
    glee_shader_link(shader, vertex_shader, fragment_shader);

    glUseProgram(shader);

    free(vb);
    free(fb);
    return shader;
}

void glee_shader_uniform_set(unsigned int shader, unsigned int float_count, const char* uniform, float* data)
{
    if (float_count == 1) {
        glUniform1f(glGetUniformLocation(shader, uniform), data[0]);
    } else if (float_count == 2) {
        glUniform2f(glGetUniformLocation(shader, uniform), data[0], data[1]);
    } else if (float_count == 3) {
        glUniform3f(glGetUniformLocation(shader, uniform), data[0], data[1], data[2]);
    } else if (float_count == 4) {
        glUniform4f(glGetUniformLocation(shader, uniform), data[0], data[1], data[2], data[3]);
    } else printf("'glee_shader_uniform_set' does not support %d floats\n", float_count);
}
