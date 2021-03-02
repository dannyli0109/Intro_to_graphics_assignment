#pragma once
#include <string>
#include "Graphics.h"
class Window
{
public:
	Window(int width, int height, std::string name);
	Window(const Window& other) = delete;
	Window& operator=(const Window& other) = delete;
	~Window();
	bool Init(int width, int height, std::string name);
	void Update();
	GLFWwindow* Get();

	glm::vec2 GetSize();
	float GetAspectRatio();
	bool Created();
	int ShouldClose();

	void SetSizeCallback(GLFWwindowsizefun callback);

	int GetKeyPress(int key);

	int GetMousePress(int key);
private:
	GLFWwindow* glfwWindow = nullptr;
	bool created = false;
};

