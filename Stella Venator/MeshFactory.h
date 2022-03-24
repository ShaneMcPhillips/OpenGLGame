#pragma once
#include "Mesh.h"
#include "glad/glad.h"
class MeshFactory
{
public:
	MeshFactory();
	Mesh createMesh(Vertex* verticies, unsigned int vertexCount, unsigned int* indicies, unsigned int drawCount);
	~MeshFactory();
};

