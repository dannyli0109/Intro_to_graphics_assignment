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
	return glm::perspective(fovY, w / h, near, far);
}

void Camera::SetAspect(int width, int height)
{
	aspect = width / (float)height;
}

void Camera::Update(float deltaTime)
{
	Window* window = Window::GetIntsance();
	float thetaR = glm::radians(theta);
	float phiR = glm::radians(phi);
	//calculate the forwards and right axes and up axis for the camera
	glm::vec3 forward(cos(phiR) * cos(thetaR), sin(phiR), cos(phiR) * sin(thetaR));
	glm::vec3 right(-sin(thetaR), 0, cos(thetaR));
	glm::vec3 up(0, 1, 0);

	float moveSpeed = 10.0f;

	if (glfwGetKey(window->Get(), GLFW_KEY_W) == GLFW_PRESS)
		position += forward * moveSpeed * deltaTime;
	if (glfwGetKey(window->Get(), GLFW_KEY_S) == GLFW_PRESS)
		position -= forward * moveSpeed * deltaTime;
	if (glfwGetKey(window->Get(), GLFW_KEY_A) == GLFW_PRESS)
		position -= right * moveSpeed * deltaTime;
	if (glfwGetKey(window->Get(), GLFW_KEY_D) == GLFW_PRESS)
		position += right * moveSpeed * deltaTime;


	double xPos, yPos;
	const float turnSpeed = 5.0f;
	glfwGetCursorPos(window->Get(), &xPos, &yPos);

	if (glfwGetMouseButton(window->Get(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		theta += turnSpeed * (xPos - lastMouseX) * deltaTime;
		phi -= turnSpeed * (yPos - lastMouseY) * deltaTime;
	}

	lastMouseX = xPos;
	lastMouseY = yPos;
}


//void Camera::Update(GLFWwindow* window, ShaderProgram* shader)
//{
//	int width, height;
//	glfwGetWindowSize(window, &width, &height);
//	this->aspect = width / (float)height;
//	shader->SetUniform("cameraPos", position);
//
//	glm::mat4 viewMat = glm::lookAt(position, center, up);
//	shader->SetUniform("viewMatrix", viewMat);
//
//	glm::mat4 projectionMat = glm::perspective(fovY, aspect, near, far);
//	shader->SetUniform("projectionMatrix", projectionMat);
//}
