#include "Window.h"

Window::Window(int width, int height, std::string name)
{
	created = Init(width, height, name);
}

Window::~Window()
{
	glfwTerminate();
}

bool Window::Init(int width, int height, std::string name)
{
	if (!glfwInit())
		return false;

	glfwWindow = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);

	if (!glfwWindow)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(glfwWindow);

	if (!gladLoadGL())
		return false;

	glfwSwapInterval(1);

	return true;
}

void Window::Update()
{
	glfwSwapBuffers(glfwWindow);
	glfwPollEvents();
}

GLFWwindow* Window::Get()
{
	return glfwWindow;
}

glm::vec2 Window::GetSize()
{
	int width;
	int height;
	glfwGetWindowSize(glfwWindow, &width, &height);
	return { width, height };
}

float Window::GetAspectRatio()
{
	int width;
	int height;
	glfwGetWindowSize(glfwWindow, &width, &height);

	return width / (float)height;
}

bool Window::Created()
{
	return created;
}

int Window::ShouldClose()
{
	return glfwWindowShouldClose(glfwWindow);
}

void Window::SetSizeCallback(GLFWwindowsizefun callback)
{
	glfwSetWindowSizeCallback(glfwWindow, callback);
}

int Window::GetKeyPress(int key)
{
	return glfwGetKey(glfwWindow, key) == GLFW_PRESS;
}

int Window::GetMousePress(int key)
{
	return glfwGetMouseButton(glfwWindow, key) == GLFW_PRESS;
}

