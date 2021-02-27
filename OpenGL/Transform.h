#pragma once

#include "Component.h"
#include "Matrices.h"
class ShaderProgram;

class Transform : public Component
{
public:
	Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale);
	virtual ~Transform() {};
	Transform(const Transform& other) = delete;
	Transform& operator=(const Transform& other) = delete;

	void SetPosition(const glm::vec3& position);
	void Translate(const glm::vec3& direction);
	void RotateX(float deg);
	void RotateY(float deg);
	void RotateZ(float deg);
	void Update(float deltaTime, ShaderProgram& shader);
private:
	glm::mat4 localTransform;
	glm::mat4 globalTransform;
};

