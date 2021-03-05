#pragma once
#include "Graphics.h"
#include "Texture.h"
#include <vector>
#include "Component.h"
#include "GUI.h"
#include <algorithm>


class ShaderProgram;

/**
 * Entity class, represents an object in the scene.
 */
class Entity
{
public:
	/**
	 * Defines components and children for the entity.
	 * The entity will update it's own components first then update the children.
	 * 
	 * \param name Name of the entity, if it is not unique, imgui might act wired
	 * \param components Pointer of components attached to the entity
	 * \param children Pointer of children entities attached to the entity
	 */
	Entity(std::string name, const std::vector<Component*>& components, const std::vector<Entity*>& children = {});
	Entity(const Entity& other) = delete;
	Entity& operator=(const Entity& other) = delete;
	~Entity();
	/**
	 * Entity will update it's component first, then update it's children.
	 * 
	 * \param deltaTime
	 */
	void Update(float deltaTime);
	void OnDraw();
	void Draw();
	void LateUpdate();
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

