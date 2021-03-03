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
	PointLight(std::vector<ShaderProgram*> shaders, const glm::vec3& color, float intensity);
	virtual ~PointLight() {};
	PointLight(const PointLight& other) = delete;
	PointLight& operator=(const PointLight& other) = delete;

	void Update(float deltaTime) override;
	void DrawGui() override;
private:
	std::vector<ShaderProgram*> shaders;
	glm::vec3 color;
	float intensity;
	int index;
	static int count;
};

