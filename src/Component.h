#pragma once
#include <vector>
#include <string>
#include "GUI.h"

class Entity;
class ShaderProgram;
class Window;

/**
 * Component base class.
 */
class Component
{
public:
	virtual ~Component() {};
	Entity* entity = nullptr;
	virtual void HandleInput(Window* window, float deltaTime) {}
	/**
	 * Update states that affects the whole scene, for example: position of the lights will update here.
	 * 
	 * \param deltaTime
	 */
	virtual void Update(float deltaTime) {}
	/**
	 * Update states that only affect the drawing of the object, for example: transform will update here.
	 * 
	 */
	virtual void OnDraw() {}
	/**
	 * Draw the mesh.
	 * 
	 */
	virtual void Draw() {}
	virtual std::string GetName() { return name; }
	virtual void Delete() { shouldDelete = true; }
	virtual bool ShouldDelete() { return shouldDelete; }
	virtual void DrawGui() {}
protected:
	std::string name = "Component";
	bool opened = true;
	bool shouldDelete = false;
};

