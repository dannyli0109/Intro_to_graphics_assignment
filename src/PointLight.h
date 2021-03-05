#pragma once
#include "Component.h"
#include "Graphics.h"
#include "GUI.h"
#include "Transform.h"
#include "ColorShadingMaterial.h"
#include <sstream>
#include "ShaderProgram.h"
#include "Material.h"

class PointLight : public Component
{
public:
	/**
	 * Point light represents the light source cast from a point to all directions.
	 * Also keeps track of a static count for how many point lights in the scene so that the value pass into the shader will be dynamic
	 * 
	 * \param shaders Shaders that will be affected by the ambient light
	 * \param color Color of the point light
	 * \param intensity Intensity of the point light
	 */
	PointLight(std::vector<ShaderProgram*> shaders, const glm::vec3& color, float intensity);
	virtual ~PointLight() {};
	PointLight(const PointLight& other) = delete;
	PointLight& operator=(const PointLight& other) = delete;

	void Update(float deltaTime) override;
	void DrawGui() override;

	static PointLight* Create(std::vector<ShaderProgram*> shaders, const glm::vec3& color, float intensity);
private:
	std::vector<ShaderProgram*> shaders;
	glm::vec3 color;
	float intensity;
	int index;
	static int count;
};

