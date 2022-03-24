#pragma once
#include "Mesh.h"
#include "glad/glad.h"
#include "stb_image.h"
#include <iostream>
class MeshFactory
{
public:
	MeshFactory();
	Mesh createMesh(Vertex* verticies, unsigned int vertexCount, 
		unsigned int* indicies, unsigned int drawCount, 
		TextureCoord* texCoords, const char* textureFile);
	~MeshFactory();
private:
	unsigned int createTexture(const char* textureFile);
};

