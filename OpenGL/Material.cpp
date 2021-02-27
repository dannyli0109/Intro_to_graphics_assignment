#include "Material.h"

Material::Material(
	const glm::vec3& ambient,
	const glm::vec3& diffuse,
	const glm::vec3& specular,
	float specularPower,
	Texture* diffuseTexture,
	Texture* normalTexture,
	Texture* specularTexture
) : ambient({ 1.0f, 1.0f, 1.0f }), diffuse({ 1.0f, 1.0f, 1.0f }), specular({ 0.0f, 0.0f, 0.0f }), specularPower(0)
{
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;

	this->specularPower = specularPower;

	this->diffuseTexture = diffuseTexture;
	this->normalTexture = normalTexture;
	this->specularTexture = specularTexture;
}

