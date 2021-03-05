#include "Material.h"

/**
 * Material base class, holds a pointer to the shader program, each material is corrispond to a single shader.
 */
Material::Material()
{
	this->name = "Material";
}

ShaderProgram* Material::GetShader()
{
	return shader;
}
