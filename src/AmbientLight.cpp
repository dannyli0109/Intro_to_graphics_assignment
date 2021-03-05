#include "AmbientLight.h"
#include "ShaderProgram.h"

/**
 * Ambient Light component, basicly just adding a color to the output
 * The shader will only output the color value without anything else.
 *
 * \param shaders Shaders that will be affected by the ambient light
 * \param color Color of the ambient light
 * \param intensity Intensity of the ambient light
 */
AmbientLight::AmbientLight(std::vector<ShaderProgram*> shaders, const glm::vec3& color, float intensity)
{
	this->name = "Ambient Light";
	this->shaders = shaders;
	this->color = color;
	this->intensity = intensity;
}

/**
 * Update the ambient light uniform parameter for each shaders.
 *
 * \param deltaTime
 */
void AmbientLight::Update(float deltaTime)
{
	for (ShaderProgram* shader : shaders)
	{
		shader->SetUniform("ambientLightIntensity", color * intensity);
	}
}

void AmbientLight::DrawGui()
{
	ImGui::ColorEdit3("Color", &color.x);
	ImGui::SliderFloat("Intensity", &intensity, 0.0f, 1.0f);	
}
