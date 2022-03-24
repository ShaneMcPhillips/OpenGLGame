#include "Mesh.h"

Mesh::Mesh(unsigned int _VAO, unsigned int _drawCount, unsigned int textureID)
{
	this->VAO = _VAO;
	this->drawCount = _drawCount;
	this->texID = textureID;
}

Mesh::~Mesh() {
}
