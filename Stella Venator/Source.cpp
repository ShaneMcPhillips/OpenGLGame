#include "WindowObject.h"
#include "Shader.h"
#include "MeshFactory.h"

int main(int argc, char** argv) {

	//Create our main display object.
	auto mainWindowObject = new WindowObject(1080, 960, "OpenGL Game", false);

	//Load GL func.
	gladLoadGL();

	//Create our main shader object. (Vertex shader & fragment shader)
	auto shader = new Shader("C:/Dev/Stella Venator/Shaders/VertexShader.glsl", "C:/Dev/Stella Venator/Shaders/FragmentShader.glsl");

	//Initialize raw mesh data.
	Vertex verticies[] = {
		glm::vec3(-0.5f, 0.5f, 0.0f), //Top left
		glm::vec3(-0.5f, -0.5f, 0.0f), //Bottom left
		glm::vec3(0.5f, -0.5f, 0.0f), //Bottom right
		glm::vec3(0.5f, 0.5f, 0.0f) //Top right
	};

	TextureCoord texCoords[] = {
		glm::vec2(0.0f, 0.0f), //Top left
		glm::vec2(0.0f, 1.0f), //Bottom left
		glm::vec2(1.0f, 1.0f), //Bottom right
		glm::vec2(1.0f, 0.0f) //Top right
	};

	unsigned int indicies[] = {
		0, 1, 3,
		3, 1, 2
	};
	/////////////////////////////////////


	//Build Mesh from MeshFactory
	MeshFactory meshFactory = MeshFactory();
	Mesh mesh1 = meshFactory.createMesh(verticies, sizeof(verticies)/sizeof(verticies[0]), //Vertex data
		indicies, sizeof(indicies) / sizeof(indicies[0]), //Index data
		texCoords, "C:/Dev/Stella Venator/Textures/planks_acacia.png"); //Texture data

	shader->bind();
	shader->setUniformInt("uTexture1", 0);
	shader->unbind();

	//Loop until the window should close.
	while (!mainWindowObject->hasWindowClosed()) {
		
		mainWindowObject->getViewportUpdate();
		
		glClearColor(0.17f, 0.35f, 0.27f, 1.0f); //Set the color of the window.
		glClear(GL_COLOR_BUFFER_BIT); //Clear the color buffer.

		shader->bind();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh1.getTextureID());
		glBindVertexArray(mesh1.getVAOID());
		glDrawElements(GL_TRIANGLES, mesh1.getDrawCount(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
		shader->unbind();

		mainWindowObject->windowBufferSwap();
		mainWindowObject->updateEvents();
	}
	//Memory cleanup.
	unsigned int vao = mesh1.getVAOID();
	glDeleteVertexArrays(1, &vao);
	delete shader;
	delete mainWindowObject;

	return EXIT_SUCCESS;
}