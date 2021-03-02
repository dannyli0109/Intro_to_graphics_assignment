#pragma once
#include "Material.h"
#include "Graphics.h"
#include "Texture.h"
#include "GUI.h"
class PhongShadingMaterial :
	public Material
{
public:
	PhongShadingMaterial(
		ShaderProgram* shader, 
		glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, float specularPower, 
		Texture* diffuseMap, Texture* normalMap, Texture* specularMap
	);

	virtual void OnDraw() override;
	virtual void DrawGui() override;

private:
	glm::vec3 ka;
	glm::vec3 kd;
	glm::vec3 ks;
	float specularPower;

	Texture* diffuseMap = nullptr;
	Texture* normalMap = nullptr;
	Texture* specularMap = nullptr;
};

