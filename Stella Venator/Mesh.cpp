#include "Mesh.h"

Mesh::Mesh(unsigned int _VAO, unsigned int _drawCount)
{
	this->VAO = _VAO;
	this->drawCount = _drawCount;
}

Mesh::~Mesh() {

}
