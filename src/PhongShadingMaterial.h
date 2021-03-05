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
	/**
	 * Phong shading material does phong lighting using diffuse, normal and specular map.
	 * 
	 * \param ka represents the ambient reflectivity
	 * \param kd represents the diffuse reflectivity
	 * \param ks represents the specular reflectivity
	 * \param specularPower represents the specular exponent
	 * \param diffuseId diffuse map id stored in the resource manager to look up the diffuse map
	 * \param normalId normal map id stored in the resource manager to look up the normal map
	 * \param specularId specular map id stored in the resource manager to look up the specular map
	 */
	PhongShadingMaterial(
		glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, float specularPower,
		std::string diffuseId,
		std::string normalId,
		std::string specularId
	);
	virtual void Update(float deltaTime) override;
	virtual void OnDraw() override;
	virtual void DrawGui() override;
	static PhongShadingMaterial* Create(
		glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, float specularPower,
		std::string diffuseId,
		std::string normalId,
		std::string specularId
	);
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

