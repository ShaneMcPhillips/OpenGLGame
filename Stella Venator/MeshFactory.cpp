#include "MeshFactory.h"

MeshFactory::MeshFactory()
{
}

Mesh MeshFactory::createMesh(Vertex* verticies, unsigned int vertexCount, 
    unsigned int* indicies, unsigned int drawCount, 
    TextureCoord* texCoords, const char* textureFile)
{
    unsigned int vao, vbo, tbo, ebo;

    //generate and bind new vertex array object.
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    //generate vertex buffer object and element buffer object + texture buffer object.
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &tbo);
    glGenBuffers(1, &ebo);
    
    //Bind VBO and buffer the data.
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(*verticies) * vertexCount, verticies, GL_STATIC_DRAW);

    //Pass in vertex array attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Bind TBO and buffer the data.
    glBindBuffer(GL_ARRAY_BUFFER, tbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(*texCoords) * vertexCount, texCoords, GL_STATIC_DRAW);
    
    //Pass in vertex array attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    //Bind the EBO and buffer the data.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(*indicies) * drawCount, indicies, GL_STATIC_DRAW);

    //Disable buffers
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    unsigned int textureID = this->createTexture(textureFile);

    return Mesh(vao, drawCount, textureID);
}

unsigned int MeshFactory::createTexture(const char* textureFile)
{
    //Create texture id and set as a 2D texture.
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    //Set texture parameters.
    //Texture parameters for how texture acts when coords are specified out of coordinate range.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //Texture parameters for how texture acts when minimized and maximized.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //Process the image data and make a texture from OpenGL.
    int width, height, numChannels;
    unsigned char* image_data = stbi_load(textureFile, &width, &height, &numChannels, 0); //Retrieve image data using stb_image library.

    //Check if we loaded the image data correctly.
    if (!image_data) {
        std::cerr << "Failed to load the texture file data for: " << textureFile << std::endl;
        return 0;
    }

    //Send the image data to opengl to be processed as a 2D texture.
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    glGenerateMipmap(GL_TEXTURE_2D); //Generate mipmaps with the bound texture.

    //Unbind the texture ID since we are finished.
    glBindTexture(GL_TEXTURE_2D, 0);

    //Free up the data from stb_image processing.
    stbi_image_free(image_data);
    return textureID;
}

MeshFactory::~MeshFactory()
{
}
