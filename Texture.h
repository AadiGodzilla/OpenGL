#ifndef TEXTURE_H

#include <glad/glad.h>
#include <stb/stb_image.h>
#include "Shader.h"

class Texture
{
	GLuint ID;
	GLenum type;
public:
	Texture();
	Texture(const char* imagePath, GLenum type, GLenum format);
	void texUnit(Shader shader, const char* uniform, int value);
	void Bind();
	void UnBind();
	void Delete();
};

#endif // !TEXTURE_H
