#include "ColorShadingMaterial.h"
#include "ShaderProgram.h"
ColorShadingMaterial::ColorShadingMaterial(ShaderProgram* shader, glm::vec3 color) : Material(shader)
{
	this->name = "Color Shading Material";
	this->color = color;
}

void ColorShadingMaterial::SetColor(glm::vec3 color)
{
	this->color = color;
}

void ColorShadingMaterial::OnDraw()
{
	shader->SetUniform("color", color);
}