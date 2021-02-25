#include "Window.h"

Window* Window::CreateInstance(int width, int height, std::string name)
{
	if (!instance)
	{
		instance = new Window(width, height, name);
	}
	return instance;
}

Window* Window::GetIntsance()
{
	return instance;
}

void Window::DeleteInstance()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

GLFWwindow* Window::Get()
{
	return glfwWindow;
}

Window::Window(int width, int height, std::string name)
{
	if (glfwInit()) {
		glfwWindow = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
	}

	if (!glfwWindow)
	{
		glfwTerminate();
	}
	else {
		glfwMakeContextCurrent(glfwWindow);
	}
}
Window* Window::instance = nullptr;
