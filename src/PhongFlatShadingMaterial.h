#pragma once
#include "Material.h"
#include "Graphics.h"
#include "GUI.h"
#include "ResourceManager.h"
class PhongFlatShadingMaterial :
	public Material
{
public:
	PhongFlatShadingMaterial(
		glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, float specularPower,
		glm::vec3 diffuseColor,
		glm::vec3 specularColor
	);
	virtual void OnDraw() override;
	virtual void DrawGui() override;

private:
	glm::vec3 ka;
	glm::vec3 kd;
	glm::vec3 ks;
	float specularPower;
	glm::vec3 diffuseColor;
	glm::vec3 specularColor;
};

