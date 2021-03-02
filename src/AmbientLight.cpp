#include "AmbientLight.h"
#include "ShaderProgram.h"

AmbientLight::AmbientLight(std::vector<ShaderProgram*> shaders, const glm::vec3& color, float intensity)
{
	this->name = "Ambient Light";
	this->shaders = shaders;
	this->color = color;
	this->intensity = intensity;
}


void AmbientLight::Update(float deltaTime)
{
	for (ShaderProgram* shader : shaders)
	{
		shader->SetUniform("ambientLightIntensity", color * intensity);
	}
}

void AmbientLight::DrawGui()
{
	if (ImGui::CollapsingHeader(name.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::ColorEdit3("Color", &color.x);
		ImGui::DragFloat("Intensity", &intensity, 1.0f, 0.0f);
	}
}
