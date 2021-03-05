#include "ColorShadingMaterial.h"
#include "ShaderProgram.h"

/**
 * The shader will only output the color value without doing anything else.
 *
 * \param color Color to shade
 */
ColorShadingMaterial::ColorShadingMaterial(glm::vec3 color)
{
	this->name = "Color Shading Material";
	this->shader = ResourceManager::GetInstance()->GetShader("color");
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

void ColorShadingMaterial::DrawGui()
{
	ImGui::ColorEdit3("Material Color", &color.x);
}
