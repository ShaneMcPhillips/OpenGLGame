#include "WindowObject.h"

WindowObject::WindowObject(unsigned int width, unsigned int height, const char* title, bool fullScreen)
{
	//Handle all GLFW errors.
	glfwSetErrorCallback(handleErrorCallback);

	this->windowProps = WindowProps();
	this->windowProps.title = title;
	
	//Set fullscreen bool properties
	if (fullScreen) {
		this->windowProps.windowMode = FULL_SCREEN;
	}
	else {
		this->windowProps.windowMode = WINDOWED_SCREEN;
	}
	this->windowContext = nullptr;
	this->monitor = nullptr;

	//Attempt to initialize glfw
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW!" << std::endl;
		return;
	}

	//Set opengl version to 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Only allow core profiling for opengl. Only using modern functions.
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

	//Create the glfw window pointer.
	this->windowContext = glfwCreateWindow(width, height, title, NULL, NULL);
	//Check if the window pointer is filled.
	if (!this->windowContext) {
		std::cerr << "Failed to create Window!" << std::endl;
		glfwTerminate();
		return;
	}
	//Tell glfw that the window is in use.
	glfwMakeContextCurrent(this->windowContext);
	glfwSwapInterval(1);
	glfwSetWindowUserPointer(this->windowContext, this);
	glfwSetWindowSizeCallback(this->windowContext, handleWindowSizeChange);
	glfwSetKeyCallback(this->windowContext, handleKeyCallback);

	this->monitor = glfwGetPrimaryMonitor();
	glfwGetWindowPos(this->windowContext, &this->windowProps.posX, &this->windowProps.posY);
	glfwGetWindowSize(this->windowContext, &this->windowProps.width, &this->windowProps.height);
	this->canViewportUpdate = true;
}

void WindowObject::windowBufferSwap()
{
	//Swaps the loaded back buffer with the current displayed front buffer
	glfwSwapBuffers(this->windowContext);
}

void WindowObject::updateEvents()
{
	//Updates input events
	glfwPollEvents();
}

void WindowObject::toggleFullscreen()
{
	if (this->windowProps.windowMode == FULL_SCREEN) {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
		
		//Refresh rate is 0 since glfw disregards it when passing nullptr as an active monitor.
		glfwSetWindowMonitor(this->windowContext, nullptr, this->windowProps.posX, this->windowProps.posY, this->windowProps.width, this->windowProps.height, 0);
		this->windowProps.windowMode = WINDOWED_SCREEN;
	}
	else {

		//backup window properties that will change with fullscreen.
		glfwGetWindowPos(this->windowContext, &this->windowProps.posX, &this->windowProps.posY);
		glfwGetWindowSize(this->windowContext, &this->windowProps.width, &this->windowProps.height);

		//Get monitor resolution
		const GLFWvidmode* vidMode = glfwGetVideoMode(this->monitor);
		glfwSetWindowMonitor(this->windowContext, this->monitor, 0, 0, vidMode->width, vidMode->height, vidMode->refreshRate);
		this->windowProps.windowMode = FULL_SCREEN;
	}
	this->canViewportUpdate = true;
}

/*
*	Called in render loop. Updates the viewport to the current size of the frame buffer after checking if the window was resized.
*/
void WindowObject::getViewportUpdate()
{
	//Check if we need to update the viewport
	if (!this->canViewportUpdate)
		return;

	//Get the size of the screen in pixels
	glfwGetFramebufferSize(this->windowContext, &this->windowProps.pWidth, &this->windowProps.pHeight);
	//Send pixel size to the viewport
	glViewport(0, 0, this->windowProps.pWidth, this->windowProps.pHeight);
	this->canViewportUpdate = false;
}

void WindowObject::handleWindowSizeChange(GLFWwindow* window, int width, int height)
{
	//Since the size of the window has changed, we need to update the viewport.
	void* ptr = glfwGetWindowUserPointer(window);
	if (WindowObject* wPtr = static_cast<WindowObject*>(ptr)) {
		wPtr->stageUpdateViewport();
	}
}

void WindowObject::handleKeyCallback(GLFWwindow* window, int keycode, int scancode, int action, int mods)
{
	void* ptr = glfwGetWindowUserPointer(window);
	if (WindowObject* wPtr = static_cast<WindowObject*>(ptr)) {
		
		if (keycode == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			wPtr->toggleFullscreen();
		}
	}
}

void WindowObject::handleErrorCallback(int error, const char* error_description)
{
	fprintf(stderr, "%s\n", error_description);
}

void WindowObject::stageUpdateViewport()
{
	this->canViewportUpdate = true;
}

WindowObject::~WindowObject()
{
	glfwDestroyWindow(this->windowContext);
	glfwTerminate();
}
