#pragma once
#include <iostream>
#include "OpenGLCore.h"

enum WindowMode {
	WINDOWED_SCREEN = 0,
	FULL_SCREEN = 1
};

struct WindowProps {
	int width, pWidth, posX;
	int height, pHeight, posY;
	const char* title;
	WindowMode windowMode;
};

class WindowObject {
public:
	WindowObject(unsigned int width, unsigned int height, const char* title, bool fullScreen);

	inline WindowProps getWindowProperties() const {
		return windowProps;
	};

	inline GLFWwindow* getWindowContext() const {
		return this->windowContext;
	};

	inline bool hasWindowClosed() const {
		return glfwWindowShouldClose(this->windowContext);
	};

	void updateWindow();

	void toggleFullscreen();

	bool getViewportUpdate();

	float getAspectRatio();

	virtual ~WindowObject();

private:
	WindowProps windowProps;
	GLFWwindow* windowContext;
	GLFWmonitor* monitor;

	bool canViewportUpdate = false;

	static void handleWindowSizeChange(GLFWwindow* window, int width, int height);
	static void handleKeyCallback(GLFWwindow* window, int keycode, int scancode, int action, int mods);
	static void handleErrorCallback(int error, const char* error_description);
	void stageUpdateViewport();

	void updateSize(int width, int height);

	bool fsToggle = false;

};

