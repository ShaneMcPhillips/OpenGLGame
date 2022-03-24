#pragma once
#include <glm/glm.hpp>
#include <glad/glad.h>
class Vertex {
public:
	Vertex(const glm::vec3& vert) {
		this->vertex = vert;
	}
private:
	glm::vec3 vertex;
};

class TextureCoord {
public:
	TextureCoord(const glm::vec2 textureCoord) {
		this->texCoord = textureCoord;
	}
private:
	glm::vec2 texCoord;
};

class Mesh
{
public:

	Mesh(unsigned int VAO, unsigned int drawCount, unsigned int textureID);

	unsigned inline int getVAOID() {
		return this->VAO;
	}

	unsigned inline int getDrawCount() {
		return this->drawCount;
	}

	unsigned inline int getTextureID() {
		return this->texID;
	}

	virtual ~Mesh();

private:
	unsigned int VAO, drawCount, texID;
};

