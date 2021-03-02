#pragma once
#include "Material.h"
#include "Graphics.h"
#include "GUI.h"
class ColorShadingMaterial :
	public Material
{

public:
	ColorShadingMaterial(ShaderProgram* shader, glm::vec3 color);
	void SetColor(glm::vec3 color);
	virtual void OnDraw() override;
private:
	glm::vec3 color;
};

