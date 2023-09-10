#include "Camera.h"

Camera* Camera::instance = nullptr;

Camera::Camera(int width, int height)
{
	this->width = width;
	this->height = height;

	cameraPos = glm::vec3(0.0f, 1.0f, 3.0f);
	cameraTarget = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	yaw = 0.0f;
	pitch = 0.0f;
}

Camera* Camera::get()
{
	if (instance == nullptr)
	{
		instance = new Camera(800, 600);
	}

	return instance;
}

bool firstMouse = true;

void Camera::mouseCallBack(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		glfwSetCursorPos(window, get()->width / 2, get()->height / 2);
		get()->lastX = 400.0f;
		get()->lastY = 300.0f;
		firstMouse = false;
	}

	float xoffset = xpos - get()->lastX;
	float yoffset = get()->lastY - ypos;

	get()->lastX = xpos;
	get()->lastY = ypos;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	get()->yaw += xoffset;
	get()->pitch += yoffset;

	if (get()->pitch > 89.0f)
		get()->pitch = 89.0f;
	if (get()->pitch < -89.0f)
		get()->pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(get()->yaw)) * cos(glm::radians(get()->pitch));
	direction.y = sin(glm::radians(get()->pitch));
	direction.z = sin(glm::radians(get()->yaw)) * cos(glm::radians(get()->pitch));
	get()->cameraTarget = glm::normalize(direction);
}

void Camera::keyInput(float deltaTime)
{
	float cameraSpeed = 5.0f * deltaTime;

	if (KeyListener::isKeyPressed(GLFW_KEY_W))
		get()->cameraPos += cameraSpeed * get()->cameraTarget;
	if (KeyListener::isKeyPressed(GLFW_KEY_S))
		get()->cameraPos -= cameraSpeed * get()->cameraTarget;
	if (KeyListener::isKeyPressed(GLFW_KEY_A))
		get()->cameraPos -= glm::normalize(glm::cross(get()->cameraTarget, get()->cameraUp)) * cameraSpeed;
	if (KeyListener::isKeyPressed(GLFW_KEY_D))
		get()->cameraPos += glm::normalize(glm::cross(get()->cameraTarget, get()->cameraUp)) * cameraSpeed;
	if (KeyListener::isKeyPressed(GLFW_KEY_LEFT_SHIFT))
		get()->cameraPos -= cameraSpeed * get()->cameraUp;
	if (KeyListener::isKeyPressed(GLFW_KEY_SPACE))
		get()->cameraPos += cameraSpeed * get()->cameraUp;
}

void Camera::Matrix(float FOV, float nearPlane, float farPlane, Shader shader, const char* uniform)
{
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);

	view = glm::lookAt(get()->cameraPos, get()->cameraPos + get()->cameraTarget, get()->cameraUp);
	proj = glm::perspective(glm::radians(FOV), (float)(get()->width / get()->height), nearPlane, farPlane);

	glUniformMatrix4fv(glGetUniformLocation(shader.getID(), uniform), 1, GL_FALSE, glm::value_ptr(proj * view));
}