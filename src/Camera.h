#pragma once
#include "Graphics.h"
#include "Window.h"
#include <iostream>


class ShaderProgram;

class Camera
{
public:
	/**
	 * Camera represents the eye looking at the scene.
	 * 
	 * \param position Vector3 of the camera position
	 * \param up Vector3 of the up vector
	 * \param theta Rotation around the y-axis
	 * \param phi Rotation around the x-axis
	 * \param fovY Field of view for Y, we make that constant so the the fovX scales with the width of the screen
	 * \param aspect Width / Height
	 * \param near Near plane distance
	 * \param far Far plane distance
	 */
	Camera(glm::vec3 position, glm::vec3 up, float theta, float phi, float fovY, float aspect, float near, float far);

	glm::vec3 GetPosition();
	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix(float w, float h);
	void SetAspect(int width, int height);
	/**
	 * Handle the input of user to move and rotate the camera.
	 * WASD to move Dragging right mouse button to rotate
	 * 
	 * \param deltaTime
	 * \param window
	 */
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