#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"

class Cube
{
	Shader shader;
	VAO vao;
	VBO vbo;
	EBO ebo;
	Texture texture;

	int indexCount;

public:
	Cube();
	Cube(Shader shader, const char* imageFile, float size);
	void Render(float x, float y, float z);
	void Delete();
};