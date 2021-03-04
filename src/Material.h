#pragma once
#include "Component.h"
class ShaderProgram;

class Material : public Component
{
public:
	Material();
	ShaderProgram* GetShader();
	virtual void OnDraw();
protected:
	ShaderProgram* shader = nullptr;
};

