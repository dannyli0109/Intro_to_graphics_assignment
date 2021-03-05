#pragma once
#include "Component.h"
class ShaderProgram;

/**
 * Material base class, holds a pointer to the shader program, each material is corrispond to a single shader.
 */
class Material : public Component
{
public:
	Material();
	ShaderProgram* GetShader();
	virtual void OnDraw() {};
protected:
	ShaderProgram* shader = nullptr;
};

