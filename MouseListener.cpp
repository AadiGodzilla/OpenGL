#include "MouseListener.h"

MouseListener* MouseListener::instance = nullptr;

MouseListener::MouseListener() 
{
	lastX = 400.0f;
	lastY = 300.0f;
	xPos = 0.0f;
	yPos = 0.0f;
}

MouseListener* MouseListener::get() 
{
	if (MouseListener::instance == nullptr)
	{
		MouseListener::instance = new MouseListener();
	}

	return MouseListener::instance;
}

void MouseListener::mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	get()->lastX = get()->xPos;
	get()->lastY = get()->yPos;

	get()->xPos = xpos;
	get()->yPos = ypos;
}

float MouseListener::getX()
{
	return (float)get()->xPos;
}
float MouseListener::getY()
{
	return (float)get()->yPos;
}
float MouseListener::getDx()
{
	return (float)(get()->lastX - get()->xPos);
}
float MouseListener::getDy()
{
	return (float)(get()->lastY - get()->yPos);
}