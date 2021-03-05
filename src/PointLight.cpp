#include "PointLight.h"
#include "Entity.h"

/**
 * Point light represents the light source cast from a point to all directions.
 *
 * \param shaders Shaders that will be affected by the ambient light
 * \param color Color of the point light
 * \param intensity Intensity of the point light
 */
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
	/*if (ImGui::CollapsingHeader(name.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
	{*/
		ImGui::ColorEdit3("Color", &color.x);
		ImGui::DragFloat("Intensity", &intensity, 1.0f, 0.0f);
	//}
}
PointLight* PointLight::Create(std::vector<ShaderProgram*> shaders, const glm::vec3& color, float intensity)
{
	return new PointLight(shaders, color, intensity);
}
int PointLight::count = 0;
