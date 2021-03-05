#pragma once
#include "Material.h"
#include "Graphics.h"
#include "GUI.h"
#include "ResourceManager.h"
class ColorShadingMaterial :
	public Material
{

public:
	/**
	 * The shader will only output the color value without doing anything else.
	 * 
	 * \param color Color to shade
	 */
	ColorShadingMaterial(glm::vec3 color);
	void SetColor(glm::vec3 color);
	virtual void OnDraw() override;
	virtual void DrawGui() override;
	static ColorShadingMaterial* Create(glm::vec3 color) {
		return new ColorShadingMaterial(color);
	};
private:
	glm::vec3 color;
};

