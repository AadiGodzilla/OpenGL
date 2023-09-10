#ifndef VAO_H

#include <glad/glad.h>
#include "VBO.h"

class VAO
{
	GLuint ID;
public:
	VAO();
	void LinkAttrib(VBO vbo, int layout, int size, int stride, void* offset);
	void Bind();
	void UnBind();
	void Delete();
};

#endif // !VAO_H
