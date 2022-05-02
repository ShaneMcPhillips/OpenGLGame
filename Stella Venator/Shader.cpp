#include "Shader.h"

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {

	std::string vertexShaderCode, fragmentShaderCode;
	std::ifstream vertexFile, fragmentFile;

	vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		vertexFile.open(vertexShaderPath);
		fragmentFile.open(fragmentShaderPath);

		std::stringstream vertexStringStream, fragmentStringStream;

		vertexStringStream << vertexFile.rdbuf();
		fragmentStringStream << fragmentFile.rdbuf();

		vertexFile.close();
		fragmentFile.close();

		vertexShaderCode = vertexStringStream.str();
		fragmentShaderCode = fragmentStringStream.str();
	}
	catch (std::ifstream::failure& e) {
		std::cerr << "Can not read shader program files!" << e.what() << std::endl;
	}

	const char* vertexShaderSource = vertexShaderCode.c_str();
	const char* fragmentShaderSource = fragmentShaderCode.c_str();

	unsigned int vertexShader = Shader::createShader(vertexShaderSource, GL_VERTEX_SHADER);
	unsigned int fragmentShader = Shader::createShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

	unsigned int shaders[] = {
		vertexShader, fragmentShader
	};

	Shader::createProgram(shaders, sizeof(shaders)/sizeof(shaders[0]));

}

void Shader::bind() {
	glUseProgram(m_programID);
}

void Shader::unbind() {
	glUseProgram(0);
}

void Shader::setUniformBool(const std::string& name, bool value) const {
	glUniform1i(glGetUniformLocation(m_programID, name.c_str()), (int)value);
}

void Shader::setUniformFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(m_programID, name.c_str()), value);
}

void Shader::setUniformInt(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(m_programID, name.c_str()), value);
}

void Shader::setUniformMat4(const std::string& name, glm::mat4 matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(this->m_programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}

Shader::~Shader() {
	glDeleteProgram(m_programID);
}

unsigned int Shader::createShader(const char* shaderSource, GLenum type) {
	unsigned int shader = glCreateShader(type);
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);

	int success;
	char errrorLog[1024];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 1024, NULL, errrorLog);
		std::cerr << "Shader " << type << " has failed to compile. [Error:] " << errrorLog << std::endl;
		return 0;
	}
	return shader;
}

void Shader::createProgram(unsigned int* shaders, unsigned int length) {
	m_programID = glCreateProgram();
	for (int i = 0; i < length; i++) {
		glAttachShader(m_programID, shaders[i]);
	}
	glLinkProgram(m_programID);

	int success;
	char errorLog[1024];

	glGetProgramiv(m_programID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(m_programID, 1024, NULL, errorLog);
		std::cerr << "Program has failed to link shaders! [Error]: " << errorLog << std::endl;
		return;
	}

	for (int i = 0; i < length; i++) {
		glDeleteShader(shaders[i]);
	}
}
