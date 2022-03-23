#include "WindowObject.h"

int main(int argc, char** argv) {

	//Create our display object.
	auto mainWindowObject = new WindowObject(1080, 960, "OpenGL Game", false);


	//Load GL func.
	gladLoadGL();

	//Shader shader("C:/Dev/Stella Venator/Shaders/VertexShader.txt", "C:/Dev/Stella Venator/Shaders/FragmentShader.txt");

	float verts[] = {
		-0.5f, 0.5f, 0.0f, //A
		-0.5f, -0.5f, 0.0f, //B
		0.5f, 0.5f, 0.0f, //C
		0.5f, -0.5f, 0.0f //D
	};

	unsigned int indicies[] = {
		0, 1, 2,
		2, 1, 3
	};



	unsigned int ebo, vao, vbo;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//Loop until the window should close.
	while (!mainWindowObject->hasWindowClosed()) {
		
		mainWindowObject->getViewportUpdate();
		
		glClearColor(0.17f, 0.35f, 0.27f, 1.0f); //Set the color of the window.
		glClear(GL_COLOR_BUFFER_BIT); //Clear the color buffer.

		//shader.bind();
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		//shader.unbind();

		mainWindowObject->windowBufferSwap();
		mainWindowObject->updateEvents();
	}

	//Memory cleanup.
	delete mainWindowObject;

	return 0;
}