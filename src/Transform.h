#pragma once

#include "Component.h"
#include "Matrices.h"
#include "GUI.h"
#include "Material.h"

class ShaderProgram;

class Transform : public Component
{
public:
	/**
	 * Transform component, defines position, rotation and scale for the object.
	 *
	 * \param position
	 * \param rotation in euler angle
	 * \param scale
	 */
	Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale);
	virtual ~Transform() {};
	Transform(const Transform& other) = delete;
	Transform& operator=(const Transform& other) = delete;

	void Update(float deltaTime) override;
	void DrawGui() override;
	virtual void OnDraw() override;

	void Set(ShaderProgram* shader);
	void SetPosition(const glm::vec3& position);
	glm::vec3 GetPosition();
	void Translate(const glm::vec3& direction);
	void RotateX(float deg);
	void RotateY(float deg);
	void RotateZ(float deg);
	glm::mat4& GetTransformMatrix();

	static Transform* Create(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale);

private:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	//glm::mat4 localTransform;
	glm::mat4 globalTransform;
};

