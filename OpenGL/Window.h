#pragma once
#include "Graphics.h"
#include <string>

class Window
{
public:
	static Window* CreateInstance(int width, int height, std::string name);
	static Window* GetIntsance();
	static void DeleteInstance();
	GLFWwindow* Get();

private:
	Window(int width, int height, std::string name);
	GLFWwindow* glfwWindow = nullptr;
	static Window* instance;
};
