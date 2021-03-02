#pragma once
#include "Graphics.h"
#include "Window.h"
#include <iostream>


class ShaderProgram;

class Camera
{
public:
	Camera(glm::vec3 position, glm::vec3 up, float theta, float phi, float fovY, float aspect, float near, float far);

	glm::vec3 GetPosition();
	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix(float w, float h);
	void SetAspect(int width, int height);
	void HandleInput(float deltaTime, Window* window);
	void Update(float deltaTime, Window* window, ShaderProgram* shader);

private:
	glm::vec3 position{ 0.0f, 0.0f, 0.0f };
	glm::vec3 up{ 0.0f, 0.0f, 0.0f };
	float theta;
	float phi;
	float aspect;
	float fovY;
	float near;
	float far;
	float lastMouseX = 0.0f;
	float lastMouseY = 0.0f;
};