#pragma once
#include <vector>
#include <string>
#include "GUI.h"

class Entity;
class ShaderProgram;
class Window;

class Component
{
public:
	virtual ~Component() {};
	Entity* entity = nullptr;
	virtual void HandleInput(Window* window, float deltaTime) {}
	virtual void Update(float deltaTime) {}
	virtual void Draw() {}
	virtual void DrawGui() {
		//ImGui::SetNextItemOpen(opened == true);
		if (ImGui::CollapsingHeader(name.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
		{
            
        }
	}
	virtual void OnDraw() {}
protected:
	std::string name = "Component";
	bool opened = true;
};

