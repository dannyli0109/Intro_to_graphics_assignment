#pragma once
#include "Component.h"
#include "Graphics.h"
#include "GUI.h"

class AmbientLight : public Component
{
public:
	/**
	 * Ambient Light component, basicly just adding a color to the output
	 * The shader will only output the color value without anything else.
	 * 
	 * \param shaders Shaders that will be affected by the ambient light
	 * \param color Color of the ambient light
	 * \param intensity Intensity of the ambient light
	 */
	AmbientLight(std::vector<ShaderProgram*> shaders, const glm::vec3& color, float intensity);
	/**
	 * Update the ambient light uniform parameter for each shaders.
	 * 
	 * \param deltaTime
	 */
	virtual void Update(float deltaTime) override;
	void DrawGui() override;
	static AmbientLight* Create(std::vector<ShaderProgram*> shaders, const glm::vec3& color, float intensity) {
		return new AmbientLight(shaders, color, intensity);
	}
private:
	std::vector<ShaderProgram*> shaders;
	glm::vec3 color;
	float intensity;
};

