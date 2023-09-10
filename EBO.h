#ifndef EBO_H
#define EBO_H

#include <glad/glad.h>

class EBO
{
	GLuint ID;
public:
	EBO();
	EBO(GLuint* indices, GLsizeiptr size);
	void Bind();
	void UnBind();
	void Delete();
};

#endif 
