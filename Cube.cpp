#include "Cube.h"

Cube::Cube()
{

}

Cube::Cube(Shader shader, const char* imageFile, float size)
{
	this->shader = shader;

	GLfloat vertices[] =
	{
		-size, size, size,		0.0f, 0.0f,
		size, size, size,		1.0f, 0.0f,
		size, -size, size,		1.0f, 0.5f,
		-size, -size, size,		0.0f, 0.5f,

		-size, size, -size,		0.0f, 0.0f,
		size, size, -size,		1.0f, 0.0f,
		size, -size, -size,		1.0f, 0.5f,
		-size, -size, -size,	0.0f, 0.5f,

		-size, size, size,		0.0f, 0.0f,
		-size, -size, size,		0.0f, 0.5f,
		-size, -size, -size,	1.0f, 0.5f,
		-size, size, -size,		1.0f, 0.0f,

		size, -size, size,		0.0f, 0.5f,
		size, size, size,		0.0f, 0.0f,
		size, size, -size,		1.0f, 0.0f,
		size, -size, -size,		1.0f, 0.5f,

		-size, size, size,		0.0f, 0.5f,
		size, size, size,		1.0f, 0.5f,
		size, size, -size,		1.0f, 1.0f,
		-size, size, -size,		0.0f, 1.0f,

		-size, -size, size,		0.0f, 0.5f,
		size, -size, size,		1.0f, 0.5f,
		size, -size, -size,		1.0f, 1.0f,
		-size, -size, -size,	0.0f, 1.0f,
	};

	GLuint indices[] =
	{
		0,1,2,
		2,3,0,

		4,5,6,
		6,7,4,

		8,9,10,
		10,11,8,

		12,13,14,
		14,15,12,

		16,17,18,
		18,19,16,

		20,21,22,
		22,23,20,
	};

	vao.Bind();

	vbo = VBO(vertices, sizeof(vertices));
	ebo = EBO(indices, sizeof(indices));

	vao.LinkAttrib(vbo, 0, 3, 5 * sizeof(float), (void*)0);
	vao.LinkAttrib(vbo, 1, 2, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	vbo.UnBind();
	vao.UnBind();
	ebo.UnBind();
	
	texture = Texture(imageFile, GL_TEXTURE_2D, GL_RGBA);
	texture.texUnit(shader, "tex", 0);

	indexCount = sizeof(indices);
}

void Cube::Render(float x, float y, float z)
{
	shader.Activate();

	glm::mat4 modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(x, y ,z));
	int modelLoc = glGetUniformLocation(shader.getID(), "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	texture.Bind();
	vao.Bind();

	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);

	vao.UnBind();
	texture.UnBind();

	shader.Deactivate();
}