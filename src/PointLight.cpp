#include "PointLight.h"
#include "Entity.h"


PointLight::PointLight(std::vector<ShaderProgram*> shaders, const glm::vec3& color, float intensity)
{
	this->name = "Point Light";

	this->shaders = shaders;
	this->color = color;
	this->intensity = intensity;
	index = count;
	count++;
}
void PointLight::Update(float deltaTime)
{
	Transform* transform = entity->GetComponent<Transform>();
	std::stringstream lightPos;
	lightPos << "lightPositions[" << index << "]";
	std::stringstream lightIntensity;
	lightIntensity << "lightIntensities[" << index << "]";
	for (ShaderProgram* shader : shaders)
	{
		shader->SetUniform(lightPos.str(), transform->GetPosition());
		shader->SetUniform(lightIntensity.str(), color * intensity);
		shader->SetUniform("lightCount", count);
	}

	ColorShadingMaterial* mat = entity->GetComponent<ColorShadingMaterial>();
	if (mat)
	{
		mat->SetColor(color);
	}
}
void PointLight::DrawGui()
{
	if (ImGui::CollapsingHeader(name.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::ColorEdit3("Color", &color.x);
		ImGui::DragFloat("Intensity", &intensity, 1.0f, 0.0f);
	}
}
int PointLight::count = 0;
