#pragma once
#include "Material.h"
#include "Graphics.h"
#include "Texture.h"
#include "GUI.h"
#include "ResourceManager.h"
class PhongShadingMaterial :
	public Material
{
public:
	PhongShadingMaterial(
		glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, float specularPower,
		std::string diffuseId,
		std::string normalId,
		std::string specularId
	);
	virtual void Update(float deltaTime) override;
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

	int selectedDiffuse = 0;
	int selectedNormal = 0;
	int selectedSpecular = 0;
};

