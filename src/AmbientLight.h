#pragma once
#include "Component.h"
#include "Graphics.h"
#include "GUI.h"
class AmbientLight : public Component
{
public:
	AmbientLight(std::vector<ShaderProgram*> shaders, const glm::vec3& color, float intensity);
	virtual void Update(float deltaTime) override;
	void DrawGui() override;
private:
	std::vector<ShaderProgram*> shaders;
	glm::vec3 color;
	float intensity;
};

