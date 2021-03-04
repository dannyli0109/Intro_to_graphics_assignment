#pragma once
#include "Material.h"
#include "Graphics.h"
#include "GUI.h"
#include "ResourceManager.h"
class ColorShadingMaterial :
	public Material
{

public:
	ColorShadingMaterial(glm::vec3 color);
	void SetColor(glm::vec3 color);
	virtual void OnDraw() override;
	virtual void DrawGui() override;
private:
	glm::vec3 color;
};

