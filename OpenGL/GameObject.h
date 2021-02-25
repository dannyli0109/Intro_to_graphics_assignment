#pragma once
#include "Graphics.h"
#include "Mesh.h"
#include "Texture.h"
#include <vector>
#include "Component.h"

class ShaderProgram;


class GameObject
{
public:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	GameObject(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
	void Update(float deltaTime);
	void Draw();
	void RotateX(float radian);
	void RotateY(float radian);
	void RotateZ(float radian);
	void Translate(float x, float y, float z);
	glm::mat4 GetModelMatrix();
	void AddChild(GameObject* child);
	void RemoveChild(GameObject* child);
	void AddComponent(Component* component);
	void RemoveComponent(Component* component);

private:
	std::vector<GameObject*> children;
	std::vector<Component*> components;
	GameObject* parent = nullptr;
};

