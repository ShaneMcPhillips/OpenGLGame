#include "MeshFactory.h"

MeshFactory::MeshFactory()
{
}

Mesh MeshFactory::createMesh(Vertex* verticies, unsigned int vertexCount, unsigned int* indicies, unsigned int drawCount)
{
    unsigned int vao, vbo, ebo;

    //generate and bind new vertex array object.
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    //generate vertex buffer object and element buffer object.
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    
    //Bind VBO and buffer the data.
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(*verticies) * vertexCount, verticies, GL_STATIC_DRAW);

    //Bind the EBO and buffer the data.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(*indicies) * drawCount, indicies, GL_STATIC_DRAW);

    //Pass in vertex array attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Disable buffers
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    Mesh mesh = Mesh(vao, drawCount);
    return mesh;
}

MeshFactory::~MeshFactory()
{
}
