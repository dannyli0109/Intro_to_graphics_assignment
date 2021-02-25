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
	void Update(float deltaTime);

private:
	glm::vec3 position;
	glm::vec3 up;
	float theta;
	float phi;
	float aspect;
	float near;
	float far;
	float fovY;
	float lastMouseX = 0.0f;
	float lastMouseY = 0.0f;
};

