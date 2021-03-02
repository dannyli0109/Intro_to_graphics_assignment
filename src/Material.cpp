#include "Material.h"

Material::Material(ShaderProgram* shader)
{
	this->name = "Material";

	this->shader = shader;
}

ShaderProgram* Material::GetShader()
{
	return shader;
}

void Material::OnDraw()
{
}
