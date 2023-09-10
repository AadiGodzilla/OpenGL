#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>

class Shader
{
private:
	std::string get_file_content(const char* filePath);
	GLuint ID;

public:
	Shader();
	Shader(const char* vertexShader, const char* fragmentShader);
	void Activate();
	void Deactivate();
	void Delete();
	GLuint getID();
};

#endif // !SHADER_H
