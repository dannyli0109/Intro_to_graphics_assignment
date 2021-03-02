#pragma once
#include "Component.h"
class ShaderProgram;

class Material : public Component
{
public:
	Material(ShaderProgram* shader);
	ShaderProgram* GetShader();
	virtual void OnDraw();
protected:
	ShaderProgram* shader;
};

