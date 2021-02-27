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

	GameObject(const std::vector<Component*>& components);
	GameObject(const GameObject& other) = delete;
	GameObject& operator=(const GameObject& other) = delete;
	~GameObject();
	void Update(float deltaTime, ShaderProgram& shader);
	void Draw();
	/*void RotateX(float radian);
	void RotateY(float radian);
	void RotateZ(float radian);
	void Translate(float x, float y, float z);
	glm::mat4 GetModelMatrix();*/
	void AddChild(GameObject* child);
	void RemoveChild(GameObject* child);
	void AddComponent(Component* component);
	void RemoveComponent(Component* component);
	GameObject* GetParent();

	/**
	 * Get specific component from game object.
	 * 
	 * \return component with specific type or nullptr if the it doesn't exists 
	 */
	template<typename T>
	T* GetComponent()
	{
		for (Component* component : components)
		{
			if (dynamic_cast<T*>(component) != nullptr)
			{
				return dynamic_cast<T*>(component);
			}
		}
		return nullptr;
	}

private:
	std::vector<GameObject*> children;
	std::vector<Component*> components;
	GameObject* parent = nullptr;
};

