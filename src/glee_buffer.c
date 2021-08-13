#include <glee.h>

/*
---------------------
 -> vertex buffers <- 
---------------------
*/

unsigned int quad_vertex_buffer_id, voxel_vertex_buffer_id;

unsigned int glee_buffer_id()
{
    unsigned int id;
    glGenVertexArrays(1, &id);
    return id;
}

void glee_buffer_attribute_set(unsigned int attribute, unsigned int float_pack, unsigned int stride, size_t offset)
{
    glEnableVertexAttribArray(attribute);
    glVertexAttribPointer(
        attribute,                           // attribute 
        float_pack,                          // size
        GL_FLOAT,                            // type
        GL_FALSE,                            // normalized?
        stride,                              // stride
        (void*)offset                        // array buffer offset
    );
}

void glee_buffer_create(unsigned int id, void* buffer, unsigned int size)
{
    if (buffer == NULL) return;
    unsigned int VBO;
    glBindVertexArray(id);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size, buffer, GL_STATIC_DRAW);
}

void glee_buffer_create_indexed(unsigned int id, void* buffer, unsigned int buffer_size, unsigned int* indices, unsigned int indices_size)
{
    if (buffer == NULL || indices == NULL) return;
    unsigned int VBO, EBO;
    glBindVertexArray(id);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, buffer_size, buffer, GL_STATIC_DRAW);  
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, indices, GL_STATIC_DRAW);
}

unsigned int glee_buffer_quad_create()
{
    float vertices[] = {
        1.0f,   1.0f,
        1.0f,   -1.0f,
        -1.0f,  -1.0f,
        -1.0f,  1.0f
    };
    unsigned int indices[] = {
        0,  1,  3,
        1,  2,  3 
    };
    unsigned int id = glee_buffer_id();
    glee_buffer_create_indexed(id, &vertices[0], sizeof(vertices), &indices[0], sizeof(indices));
    glee_buffer_attribute_set(0, 2, 0, 0);
    return id;
}

unsigned int glee_buffer_voxel_create()
{
    float vertices[] = {
        -1.0f,  -1.0f,  -1.0f, 
        -1.0f,  -1.0f,  1.0f,
        -1.0f,  1.0f,   1.0f, 
        1.0f,   1.0f,   -1.0f, 
        -1.0f,  -1.0f,  -1.0f,
        -1.0f,  1.0f,   -1.0f, 
        1.0f,   -1.0f,  1.0f,
        -1.0f,  -1.0f,  -1.0f,
        1.0f,   -1.0f,  -1.0f,
        1.0f,   1.0f,   -1.0f,
        1.0f,   -1.0f,  -1.0f,
        -1.0f,  -1.0f,  -1.0f,
        -1.0f,  -1.0f,  -1.0f,
        -1.0f,  1.0f,   1.0f,
        -1.0f,  1.0f,   -1.0f,
        1.0f,   -1.0f,  1.0f,
        -1.0f,  -1.0f,  1.0f,
        -1.0f,  -1.0f,  -1.0f,
        -1.0f,  1.0f,   1.0f,
        -1.0f,  -1.0f,  1.0f,
        1.0f,   -1.0f,  1.0f,
        1.0f,   1.0f,   1.0f,
        1.0f,   -1.0f,  -1.0f,
        1.0f,   1.0f,   -1.0f,
        1.0f,   -1.0f,  -1.0f,
        1.0f,   1.0f,   1.0f,
        1.0f,   -1.0f,  1.0f,
        1.0f,   1.0f,   1.0f,
        1.0f,   1.0f,   -1.0f,
        -1.0f,  1.0f,   -1.0f,
        1.0f,   1.0f,   1.0f,
        -1.0f,  1.0f,   -1.0f,
        -1.0f,  1.0f,   1.0f,
        1.0f,   1.0f,   1.0f,
        -1.0f,  1.0f,   1.0f,
        1.0f,   -1.0f,  1.0f
    };
    unsigned int id = glee_buffer_id();
    glee_buffer_create(id, &vertices[0], sizeof(vertices));
    glee_buffer_attribute_set(0, 3, 0, 0);
    return id;
}

void glee_buffer_voxel_texcoords(unsigned int id)
{
    float texcoords[] = {
        0.0f,   1.0f,
        1.0f,   1.0f,
        1.0f,   0.0f,
        0.0f,   0.0f,
        1.0f,   1.0f,
        1.0f,   0.0f,
        0.0f,   0.0f,
        1.0f,   1.0f,
        1.0f,   0.0f,
        0.0f,   0.0f,
        0.0f,   1.0f,
        1.0f,   1.0f,
        0.0f,   1.0f,
        1.0f,   0.0f,
        0.0f,   0.0f,
        0.0f,   0.0f,
        0.0f,   1.0f,
        1.0f,   1.0f,
        0.0f,   0.0f,
        0.0f,   1.0f,
        1.0f,   1.0f,
        0.0f,   0.0f,
        1.0f,   1.0f,
        1.0f,   0.0f,
        1.0f,   1.0f,
        0.0f,   0.0f,
        0.0f,   1.0f,
        0.0f,   1.0f,
        1.0f,   1.0f,
        1.0f,   0.0f,
        0.0f,   1.0f,
        1.0f,   0.0f,
        0.0f,   0.0f,
        1.0f,   0.0f,
        0.0f,   0.0f,
        1.0f,   1.0f,
    };
    glee_buffer_create(id, &texcoords[0], sizeof(texcoords));
    glee_buffer_attribute_set(1, 2, 0, 0);
}

unsigned int glee_buffer_skybox_create()
{
    float vertices[] = {        
        -1.0f,  1.0f,   -1.0f,
        -1.0f,  -1.0f,  -1.0f,
        1.0f,   -1.0f,  -1.0f,
        1.0f,   -1.0f,  -1.0f,
        1.0f,   1.0f,   -1.0f,
        -1.0f,  1.0f,   -1.0f,
        -1.0f,  -1.0f,  1.0f,
        -1.0f,  -1.0f,  -1.0f,
        -1.0f,  1.0f,   -1.0f,
        -1.0f,  1.0f,   -1.0f,
        -1.0f,  1.0f,   1.0f,
        -1.0f,  -1.0f,  1.0f,
        1.0f,   -1.0f,  -1.0f,
        1.0f,   -1.0f,  1.0f,
        1.0f,   1.0f,   1.0f,
        1.0f,   1.0f,   1.0f,
        1.0f,   1.0f,   -1.0f,
        1.0f,   -1.0f,  -1.0f,
        -1.0f,  -1.0f,  1.0f,
        -1.0f,  1.0f,   1.0f,
        1.0f,   1.0f,   1.0f,
        1.0f,   1.0f,   1.0f,
        1.0f,   -1.0f,  1.0f,
        -1.0f,  -1.0f,  1.0f,
        -1.0f,  1.0f,   -1.0f,
        1.0f,   1.0f,   -1.0f,
        1.0f,   1.0f,   1.0f,
        1.0f,   1.0f,   1.0f,
        -1.0f,  1.0f,   1.0f,
        -1.0f,  1.0f,   -1.0f,
        -1.0f,  -1.0f,  -1.0f,
        -1.0f,  -1.0f,  1.0f,
        1.0f,   -1.0f,  -1.0f,
        1.0f,   -1.0f,  -1.0f,
        -1.0f,  -1.0f,  1.0f,
        1.0f,   -1.0f,  1.0f
    };
    unsigned int id = glee_buffer_id();
    glee_buffer_create(id, &vertices[0], sizeof(vertices));
    glee_buffer_attribute_set(0, 3, 0, 0);
    return id;
}