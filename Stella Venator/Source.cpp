#include "WindowObject.h"
#include "Shader.h"
#include "MeshFactory.h"
#include <glm/gtc/matrix_transform.hpp>

int main(int argc, char** argv) {

	//Create our main display object.
	auto mainWindowObject = new WindowObject(1080, 960, "OpenGL Game", false);

	//Load GL func.
	gladLoadGL();

	//Create our main shader object. (Vertex shader & fragment shader)
	auto shader = new Shader("C:/Dev/Stella Venator/Shaders/VertexShader.glsl", "C:/Dev/Stella Venator/Shaders/FragmentShader.glsl");

	//Initialize raw mesh data.
	Vertex verticies[] = {
		/*glm::vec3(-0.5f, 0.5f, 0.0f), //Top left
		glm::vec3(-0.5f, -0.5f, 0.0f), //Bottom left
		glm::vec3(0.5f, -0.5f, 0.0f), //Bottom right
		glm::vec3(0.5f, 0.5f, 0.0f) //Top right*/

		
		glm::vec3(-0.5f,0.5f,-0.5f),
		glm::vec3(-0.5f,-0.5f,-0.5f),
		glm::vec3(0.5f,-0.5f,-0.5f),
		glm::vec3(0.5f,0.5f,-0.5f),

		glm::vec3(-0.5f,0.5f,0.5f),
		glm::vec3(-0.5f,-0.5f,0.5f),
		glm::vec3(0.5f,-0.5f,0.5f),
		glm::vec3(0.5f,0.5f,0.5f),

		glm::vec3(0.5f,0.5f,-0.5f),
		glm::vec3(0.5f,-0.5f,-0.5f),
		glm::vec3(0.5f,-0.5f,0.5f),
		glm::vec3(0.5f,0.5f,0.5f),

		glm::vec3(-0.5f,0.5f,-0.5f),
		glm::vec3(-0.5f,-0.5f,-0.5f),
		glm::vec3(-0.5f,-0.5f,0.5f),
		glm::vec3(-0.5f,0.5f,0.5f),

		glm::vec3(-0.5f,0.5f,0.5f),
		glm::vec3(-0.5f,0.5f,-0.5f),
		glm::vec3(0.5f,0.5f,-0.5f),
		glm::vec3(0.5f,0.5f,0.5f),

		glm::vec3(-0.5f,-0.5f,0.5f),
		glm::vec3(-0.5f,-0.5f,-0.5f),
		glm::vec3(0.5f,-0.5f,-0.5f),
		glm::vec3(0.5f,-0.5f,0.5f)
	};

	TextureCoord texCoords[] = {
		/*glm::vec2(0.0f, 0.0f), //Top left
		glm::vec2(0.0f, 1.0f), //Bottom left
		glm::vec2(1.0f, 1.0f), //Bottom right
		glm::vec2(1.0f, 0.0f) //Top right*/

		glm::vec2(0,0),
		glm::vec2(0,1),
		glm::vec2(1,1),
		glm::vec2(1,0),
		glm::vec2(0,0),
		glm::vec2(0,1),
		glm::vec2(1,1),
		glm::vec2(1,0),
		glm::vec2(0,0),
		glm::vec2(0,1),
		glm::vec2(1,1),
		glm::vec2(1,0),
		glm::vec2(0,0),
		glm::vec2(0,1),
		glm::vec2(1,1),
		glm::vec2(1,0),
		glm::vec2(0,0),
		glm::vec2(0,1),
		glm::vec2(1,1),
		glm::vec2(1,0),
		glm::vec2(0,0),
		glm::vec2(0,1),
		glm::vec2(1,1),
		glm::vec2(1,0)
		
	};

	unsigned int indicies[] = {
		/*0, 1, 3,
		3, 1, 2*/

		0,1,3,
		3,1,2,
		4,5,7,
		7,5,6,
		8,9,11,
		11,9,10,
		12,13,15,
		15,13,14,
		16,17,19,
		19,17,18,
		20,21,23,
		23,21,22

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

	float aspect = 0.0f;

	glEnable(GL_DEPTH_TEST);

	//Loop until the window should close.
	while (!mainWindowObject->hasWindowClosed()) {
		if (mainWindowObject->getViewportUpdate()) {
			aspect = mainWindowObject->getAspectRatio();
		}
		
		glClearColor(0.17f, 0.35f, 0.27f, 1.0f); //Set the color of the window.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear the color buffer.


		//Process Model matrix
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(-55.0f), glm::vec3(0.5, 1.0, 0.0));

		glm::mat4 view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));

		glm::mat4 projection = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);


		shader->bind();

		shader->setUniformMat4("modelMatrix", model);
		shader->setUniformMat4("viewMatrix", view);
		shader->setUniformMat4("projectionMatrix", projection);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh1.getTextureID());
		glBindVertexArray(mesh1.getVAOID());
		glDrawElements(GL_TRIANGLES, mesh1.getDrawCount(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
		shader->unbind();

		mainWindowObject->updateWindow();
	}
	//Memory cleanup.
	meshFactory.cleanUp();
	delete shader;
	delete mainWindowObject;

	return EXIT_SUCCESS;
}