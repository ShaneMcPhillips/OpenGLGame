#pragma once
#include <glm/glm.hpp>
class Vertex {
public:
	Vertex(const glm::vec3& vert) {
		this->vertex = vert;
	}
private:
	glm::vec3 vertex;
};

class Mesh
{
public:

	Mesh(unsigned int VAO, unsigned int drawCount);

	unsigned inline int getVAOID() {
		return this->VAO;
	}

	unsigned inline int getDrawCount() {
		return this->drawCount;
	}
	virtual ~Mesh();

private:
	unsigned int VAO, drawCount;
};

