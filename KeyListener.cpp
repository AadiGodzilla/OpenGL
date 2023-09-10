#include "KeyListener.h"

KeyListener* KeyListener::instance = nullptr;

KeyListener::KeyListener()
{
	for (int i = 0; i < sizeof(KeyListener::keyPressed); i++)
	{
		KeyListener::keyPressed[i] = false;
	}
}

KeyListener* KeyListener::get()
{
	if (KeyListener::instance == nullptr)
	{
		KeyListener::instance = new KeyListener();
	}

	return KeyListener::instance;
}

void KeyListener::keyCallBack(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		KeyListener::get()->keyPressed[key] = true;
	}
	if (action == GLFW_RELEASE)
	{
		KeyListener::get()->keyPressed[key] = false;
	}
}

bool KeyListener::isKeyPressed(int keyCode)
{
	return KeyListener::get()->keyPressed[keyCode];
}