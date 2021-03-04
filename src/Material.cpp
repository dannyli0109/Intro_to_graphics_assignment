#include "Material.h"

Material::Material()
{
	this->name = "Material";
}

ShaderProgram* Material::GetShader()
{
	return shader;
}

void Material::OnDraw()
{
}
