#ifndef VBO_H
#define VBO_H

#include <glad/glad.h>

class VBO
{
	GLuint ID;
public:
	VBO();
	VBO(GLfloat* vertices, GLsizeiptr size);
	void Bind();
	void UnBind();
	void Delete();
};

#endif // !VBO_H

