#pragma once
#include <string>
#include "Graphics.h"
class Window
{
public:
	/**
	 * Window class the encapsulate the glfw api.
	 * 
	 * \param width width of the window
	 * \param height height of the window
	 * \param name name of the window
	 */
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
	bool ShouldUpdateSize();

	void SetSizeCallback(GLFWwindowsizefun callback);

	int GetKeyPress(int key);

	int GetMousePress(int key);
private:
	GLFWwindow* glfwWindow = nullptr;
	bool created = false;
	int width;
	int height;
};

