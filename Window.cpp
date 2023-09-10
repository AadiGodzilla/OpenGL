#include "Window.h"

Window* Window::instance = nullptr;

Shader shader;
std::vector<std::vector<std::vector<Cube>>> cubes;

float beginTime;
float endTime;
float deltaTime = 0.0f;

Window::Window()
{
	this->screenWidth = 800;
	this->screenHeight = 600;
	this->screenTitle = "Hello World!!";
}

Window* Window::get()
{
	if (Window::instance == nullptr)
	{
		Window::instance = new Window();
	}

	return Window::instance;
}

void Window::run()
{
	Window::init();
	Window::loop();
}

void Window::init()
{
	glfwSetErrorCallback(NULL);

	if (!glfwInit()) {
		std::cout << "Unable to initialize glfw" << "\n";
		exit(0);
	}

	glfwDefaultWindowHints();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(screenWidth, screenHeight, screenTitle, NULL, NULL);

	if (window == nullptr)
	{
		std::cout << "Unable to create glfw window\t" << "\n";
		exit(0);
	}

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, Camera::mouseCallBack);
	glfwSetKeyCallback(window, KeyListener::keyCallBack);

	glfwMakeContextCurrent(window);

	gladLoadGL();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	shader = Shader("VertexShader.glsl", "FragmentShader.glsl");

	int maxCubes = 16;

	for (size_t i = 0; i < maxCubes; i++)
	{
		std::vector<std::vector<Cube>> row;

		for (size_t j = 0; j < maxCubes; j++)
		{
			std::vector<Cube> col;

			for (size_t k = 0; k < maxCubes; k++)
			{
				col.push_back(Cube(shader, "dirt_grass_atlas.png", 0.5f));
			}

			row.push_back(col);
		}	

		cubes.push_back(row);
	}

	beginTime = glfwGetTime();

	glfwShowWindow(window);
}

void Window::loop()
{
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		endTime = glfwGetTime();
		deltaTime = (endTime - beginTime);
		beginTime = endTime;

		glClearColor(0.34f, 0.45f, 0.60f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.Activate();

		Camera::keyInput(deltaTime);
		Camera::Matrix(45.0f, 0.1f, 100.0f, shader, "cameraMatrix");

		for (size_t i = 0; i < cubes.size(); i++)
		{
			for (size_t j = 0; j < cubes[i].size(); j++)
			{
				for (size_t k = 0; k < cubes[i][j].size(); k++)
				{
					cubes[i][j][k].Render((float)i, (float)j, (float)k);
				}
			}
		}

		glfwSwapBuffers(window);
	}
}