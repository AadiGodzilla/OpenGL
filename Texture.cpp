#include "Texture.h"

Texture::Texture()
{

}

Texture::Texture(const char* imagePath, GLenum type, GLenum format)
{
	this->type = type;

	int widthImg, heightImg, channels;
	unsigned char* bytes = stbi_load(imagePath, &widthImg, &heightImg, &channels, 0);

	glGenTextures(1, &ID);
	glBindTexture(type, ID);

	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(type, 0, format, widthImg, heightImg, 0, format, GL_UNSIGNED_BYTE, bytes);
	glGenerateMipmap(type);

	stbi_image_free(bytes);
	glBindTexture(type, 0);
}

void Texture::texUnit(Shader shader, const char* uniform, int value)
{
	shader.Activate();
	int texLoc = glGetUniformLocation(shader.getID(), uniform);
	glUniform1i(texLoc, value);
	shader.Deactivate();
}

void Texture::Bind()
{
	glBindTexture(type, ID);
}

void Texture::UnBind()
{
	glBindTexture(type, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}