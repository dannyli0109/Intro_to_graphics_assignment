#pragma once
#include <vector>

class GameObject;

class Component
{
public:
	GameObject* gameObject = nullptr;
	virtual void Update(float deltaTime) = 0;
	virtual void Remove() = 0;
	virtual void Draw() = 0;
private:

};

