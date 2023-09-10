#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "KeyListener.h"

class Camera
{
	static Camera* instance;

	glm::vec3 cameraPos;
	glm::vec3 cameraTarget;
	glm::vec3 cameraUp;

	int width, height;
	float lastX, lastY;
	float yaw, pitch;

	Camera(int width, int height);

public:
	static Camera* get();
	static void Matrix(float FOV, float nearPlane, float farPlane, Shader shader, const char* uniform);
	static void keyInput(float deltaTime);
	static void mouseCallBack(GLFWwindow* window, double xpos, double ypos);
};

#endif