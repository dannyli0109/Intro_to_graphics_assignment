#pragma once
#include "Material.h"
#include "Graphics.h"
#include "GUI.h"
#include "ResourceManager.h"

class PhongFlatShadingMaterial :
	public Material
{
public:
	/**
	 * Phong flat shading material does phong lighting using color only.
	 * 
	 * \param ka represents the ambient reflectivity
	 * \param kd represents the diffuse reflectivity
	 * \param ks represents the specular reflectivity
	 * \param specularPower represents the specular exponent
	 * \param diffuseColor represents the diffuse color for the material
	 * \param specularColor represents the specular color for the material
	 */
	PhongFlatShadingMaterial(
		glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, float specularPower,
		glm::vec3 diffuseColor,
		glm::vec3 specularColor
	);
	virtual void OnDraw() override;
	virtual void DrawGui() override;
	static PhongFlatShadingMaterial* Create(
		glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, float specularPower,
		glm::vec3 diffuseColor,
		glm::vec3 specularColor);

private:
	glm::vec3 ka;
	glm::vec3 kd;
	glm::vec3 ks;
	float specularPower;
	glm::vec3 diffuseColor;
	glm::vec3 specularColor;
};

