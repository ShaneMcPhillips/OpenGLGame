#pragma once

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
class Shader
{
public:
	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
	void bind();
	void unbind();
	void setUniformBool(const std::string& name, bool value) const;
	void setUniformFloat(const std::string& name, float value) const;
	void setUniformInt(const std::string& name, int value) const;
	~Shader();
private:
	unsigned int m_programID = 0;
	unsigned int createShader(const char *shaderSource, GLenum type);
	void createProgram(unsigned int* shaders, unsigned int length);
};

