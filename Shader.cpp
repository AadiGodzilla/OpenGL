#include "Shader.h"

std::string Shader::get_file_content(const char* filePath)
{
	std::fstream inputFile(filePath);

	std::stringstream buffer;

	buffer << inputFile.rdbuf();

	return buffer.str();
}

Shader::Shader()
{

}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	std::string vertexSourceString = get_file_content(vertexFile);
	std::string fragmentSourceString = get_file_content(fragmentFile);

	const char* vertexSource = vertexSourceString.c_str();
	const char* fragmentSource = fragmentSourceString.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Activate()
{
	glUseProgram(ID);
}

void Shader::Deactivate()
{
	glUseProgram(0);
}

void Shader::Delete()
{
	glDeleteProgram(ID);
}

GLuint Shader::getID()
{
	return ID;
}