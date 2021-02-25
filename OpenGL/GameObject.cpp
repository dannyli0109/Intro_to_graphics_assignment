#include "GameObject.h"
#include "ShaderProgram.h"

GameObject::GameObject(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
}

void GameObject::Update(float deltaTime)
{
}

void GameObject::Draw()
{
	/*mesh->Draw();*/
}

void GameObject::RotateX(float radian)
{
	rotation.x = radian;
}

void GameObject::RotateY(float radian)
{
	rotation.y = radian;
}

void GameObject::RotateZ(float radian)
{
	rotation.z = radian;
}

void GameObject::Translate(float x, float y, float z)
{
	position.x += x;
	position.y += y;
	position.z += z;
}

glm::mat4 GameObject::GetModelMatrix()
{
	glm::mat4 modelMat(1.0f);
	modelMat = glm::translate(modelMat, position);
	modelMat = glm::scale(modelMat, scale);
	modelMat = glm::rotate(modelMat, rotation.z, glm::vec3(0, 0, 1));
	modelMat = glm::rotate(modelMat, rotation.y, glm::vec3(0, 1, 0));
	modelMat = glm::rotate(modelMat, rotation.x, glm::vec3(1, 0, 0));

	return modelMat;
}

void GameObject::AddChild(GameObject* child)
{
	child->parent = this;
	children.push_back(child);
}

void GameObject::RemoveChild(GameObject* child)
{
	auto position = std::find(children.begin(), children.end(), child);
	if (position != children.end())
	{
		children.erase(position);
		child->parent = nullptr;
	}
}

void GameObject::AddComponent(Component* component)
{
	components.push_back(component);
}

void GameObject::RemoveComponent(Component* component)
{
	auto position = std::find(components.begin(), components.end(), component);
	if (position != components.end())
	{
		components.erase(position);
	}
}
