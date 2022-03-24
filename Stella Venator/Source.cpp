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
		glm::vec3(-0.5f, 0.5f, 0.0f),
		glm::vec3(-0.5f, -0.5f, 0.0f),
		glm::vec3(0.5f, 0.5f, 0.0f),
		glm::vec3(0.5f, -0.5f, 0.0f)
	};

	unsigned int indicies[] = {
		0, 1, 2,
		2, 1, 3
	};
	/////////////////////////////////////


	//Build Mesh from MeshFactory
	MeshFactory meshFactory = MeshFactory();
	Mesh mesh1 = meshFactory.createMesh(verticies, sizeof(verticies)/sizeof(verticies[0]), indicies, sizeof(indicies) / sizeof(indicies[0]));

	//Loop until the window should close.
	while (!mainWindowObject->hasWindowClosed()) {
		
		mainWindowObject->getViewportUpdate();
		
		glClearColor(0.17f, 0.35f, 0.27f, 1.0f); //Set the color of the window.
		glClear(GL_COLOR_BUFFER_BIT); //Clear the color buffer.

		shader->bind();
		glBindVertexArray(mesh1.getVAOID());
		glDrawElements(GL_TRIANGLES, mesh1.getDrawCount(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		shader->unbind();

		mainWindowObject->windowBufferSwap();
		mainWindowObject->updateEvents();
	}

	//Memory cleanup.
	delete shader;
	delete mainWindowObject;

	return 0;
}