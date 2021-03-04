#include "Camera.h"
#include "ShaderProgram.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float theta, float phi, float fovY, float aspect, float near, float far)
{
	this->position = position;
	this->up = up;
	this->theta = theta;
	this->phi = phi;
	this->aspect = aspect;
	this->near = near;
	this->far = far;
	this->fovY = fovY;
}

glm::vec3 Camera::GetPosition()
{
	return position;
}

glm::mat4 Camera::GetViewMatrix()
{
	float thetaR = glm::radians(theta);
	float phiR = glm::radians(phi);
	glm::vec3 forward(std::cos(phiR) * std::cos(thetaR), std::sin(phiR), std::cos(phiR) * std::sin(thetaR));
	return glm::lookAt(position, position + forward, up);
}

glm::mat4 Camera::GetProjectionMatrix(float w, float h)
{
	if (h == 0) return glm::mat4(1);
	return glm::perspective(fovY, w / h, near, far);
}

void Camera::SetAspect(int width, int height)
{
	aspect = width / (float)height;
}

void Camera::HandleInput(float deltaTime, Window* window)
{
	float thetaR = glm::radians(theta);
	float phiR = glm::radians(phi);
	//calculate the forwards and right axes and up axis for the camera
	glm::vec3 forward(cos(phiR) * cos(thetaR), sin(phiR), cos(phiR) * sin(thetaR));
	glm::vec3 right(-sin(thetaR), 0, cos(thetaR));
	glm::vec3 up(0, 1, 0);

	float moveSpeed = 10.0f;

	if (window->GetKeyPress(GLFW_KEY_W))
		position += forward * moveSpeed * deltaTime;
	if (window->GetKeyPress(GLFW_KEY_S))
		position -= forward * moveSpeed * deltaTime;
	if (window->GetKeyPress(GLFW_KEY_A))
		position -= right * moveSpeed * deltaTime;
	if (window->GetKeyPress(GLFW_KEY_D))
		position += right * moveSpeed * deltaTime;

	double xPos, yPos;
	const float turnSpeed = 5.0f;
	glfwGetCursorPos(window->Get(), &xPos, &yPos);

	if (window->GetMousePress(GLFW_MOUSE_BUTTON_RIGHT))
	{
		theta += turnSpeed * (xPos - lastMouseX) * deltaTime;
		phi -= turnSpeed * (yPos - lastMouseY) * deltaTime;
	}

	lastMouseX = xPos;
	lastMouseY = yPos;
}


void Camera::Update(float deltaTime, Window* window, ShaderProgram* shader)
{
	glm::vec2 windowSize = window->GetSize();
	glm::vec3 cameraPos = GetPosition();
	glm::mat4 cameraViewMatrix = GetViewMatrix();
	glm::mat4 cameraProjectionMatrix = GetProjectionMatrix(windowSize.x, windowSize.y);

	shader->SetUniform("cameraPos", cameraPos);
	shader->SetUniform("viewMatrix", cameraViewMatrix);
	shader->SetUniform("projectionMatrix", cameraProjectionMatrix);
}


