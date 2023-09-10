#ifndef WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>

#include "Shader.h"
#include "Cube.h"
#include "Camera.h"
#include "KeyListener.h"

class Window
{
	static Window* instance;

	int screenWidth;
	int screenHeight;
	const char* screenTitle;

	GLFWwindow* window;

	Window();
public:
	static Window* get();
	void run();
	void init();
	void loop();
};

#endif // !WINDOW_H

