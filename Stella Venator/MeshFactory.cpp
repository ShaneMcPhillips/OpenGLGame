#include "MeshFactory.h"

MeshFactory::MeshFactory()
{
}

Mesh MeshFactory::createMesh(Vertex* verticies, unsigned int vertexCount, 
    unsigned int* indicies, unsigned int drawCount, 
    TextureCoord* texCoords, const char* textureFile)
{
    unsigned int vao;
    //generate and bind new vertex array object.
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    //Store data into buffer objects and set correct attribute indexes.
    this->storeAttributePointer(0, 3, sizeof(*verticies) * vertexCount, verticies);
    this->storeAttributePointer(1, 2, sizeof(*texCoords) * vertexCount, texCoords);
    //Store data into the index buffer for more efficient draw calls.
    this->storeIndexBuffer(indicies, drawCount);

    //Disable bound buffers.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //Add vertex array object to vector list for clean up later
    this->arrayObjects.push_back(vao);

    //Grab texture ID and add to vector list for clean up later
    unsigned int textureID = this->createTexture(textureFile);
    this->textureObjects.push_back(textureID);
    //Return Mesh Object. No need to return object as dynamically allocated memory, Mesh Object copies are completely OK here
    return Mesh(vao, drawCount, textureID);
}

void MeshFactory::cleanUp()
{
    //Delete buffers from vector list, then clean vector list (for each known buffer object)
    glDeleteBuffers(this->bufferObjects.size(), this->bufferObjects.data());
    this->bufferObjects.clear();
    glDeleteTextures(this->textureObjects.size(), this->textureObjects.data());
    this->textureObjects.clear();
    glDeleteVertexArrays(this->arrayObjects.size(), this->arrayObjects.data());
    this->arrayObjects.clear();
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

void MeshFactory::storeAttributePointer(unsigned int attributeIndex, unsigned int attributeValueSize, GLsizeiptr size, const void* data)
{
    //generate vertex buffer object
    unsigned int vbo;
    glGenBuffers(1, &vbo);
    //Bind the buffer and buffer the data to the bound buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    //Enable the vertex attribute at the specified index
    glEnableVertexAttribArray(attributeIndex);
    //Set the attribute pointer data to the specified index
    glVertexAttribPointer(attributeIndex, attributeValueSize, GL_FLOAT, GL_FALSE, 0, 0);
    //Store the vertex buffer object with others to clean up later
    this->bufferObjects.push_back(vbo);
}

void MeshFactory::storeIndexBuffer(unsigned int* indicies, unsigned int indexCount)
{
    //generate element buffer object
    unsigned int ebo;
    glGenBuffers(1, &ebo);
    //Bind the element buffer and send the data to the bound buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(*indicies) * indexCount, indicies, GL_STATIC_DRAW);
    //Store buffer object with others to clean up later
    this->bufferObjects.push_back(ebo);
}

MeshFactory::~MeshFactory()
{
}
