#ifndef KEYLISTENER_H
#define KEYLISTENER_H

#include <GLFW/glfw3.h>

class  KeyListener
{
	static KeyListener *instance;
	bool keyPressed[1024];
	KeyListener();

public:
	static KeyListener *get();
	static void keyCallBack(GLFWwindow *window, int key, int scancode, int action, int mods);
	static bool isKeyPressed(int keyCode);
};

#endif