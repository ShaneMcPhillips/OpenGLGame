#pragma once
#include "Mesh.h"
#include "glad/glad.h"
#include "stb_image.h"
#include <iostream>
#include <vector>
class MeshFactory
{
public:
	MeshFactory();
	Mesh createMesh(Vertex* verticies, unsigned int vertexCount, 
		unsigned int* indicies, unsigned int drawCount, 
		TextureCoord* texCoords, const char* textureFile);
	void cleanUp();
	~MeshFactory();
private:
	unsigned int createTexture(const char* textureFile);

	void storeAttributePointer(unsigned int attributeIndex, unsigned int attributeValueSize, GLsizeiptr size, const void *data);
	void storeIndexBuffer(unsigned int* indicies, unsigned int indexCount);

	std::vector<unsigned int> bufferObjects;
	std::vector<unsigned int> arrayObjects;
	std::vector<unsigned int> textureObjects;
};

