#pragma once
#include "Graphics.h"

class Texture;


class Material
{
public:
	Material(
		const glm::vec3& ambient,
		const glm::vec3& diffuse,
		const glm::vec3& specular,
		float specularPower,
		Texture* diffuseTexture,
		Texture* normalTexture,
		Texture* specularTexture
	);

private:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	float specularPower;

	Texture* diffuseTexture = nullptr;
	Texture* normalTexture = nullptr;
	Texture* specularTexture = nullptr;
};

