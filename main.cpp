#include "Window.h"

int main(int, char **)
{
	Window* window = Window::get();
	window->run();

	return 0;
}