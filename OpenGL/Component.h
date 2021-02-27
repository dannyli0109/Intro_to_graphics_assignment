#pragma once
#include <vector>

class GameObject;
class ShaderProgram;

class Component
{
public:
	virtual ~Component() {};
	GameObject* gameObject = nullptr;
	virtual void Update(float deltaTime, ShaderProgram& shader) = 0;
private:

};

