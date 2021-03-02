#pragma once
#include "Graphics.h"
#include "Mesh.h"
#include "Texture.h"
#include <vector>
#include "Component.h"
#include "GUI.h"


class ShaderProgram;


class Entity
{
public:

	Entity(std::string name, const std::vector<Component*>& components);
	Entity(const Entity& other) = delete;
	Entity& operator=(const Entity& other) = delete;
	~Entity();
	void Update(float deltaTime);
	void Draw();
	void AddChild(Entity* child);
	void RemoveChild(Entity* child);
	void AddComponent(Component* component);
	void RemoveComponent(Component* component);
	Entity* GetParent();
	std::string GetName();

	void DrawGui();

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
	std::string name;
	std::vector<Entity*> children;
	std::vector<Component*> components;
	Entity* parent = nullptr;
};

