#include "PointLight.h"

PointLight::PointLight(glm::vec3 position, glm::vec3 intensity)
{
	this->position = position;
	this->intensity = intensity;
}

glm::vec3 PointLight::GetPosition()
{
	return position;
}

glm::vec3 PointLight::GetIntensity()
{
	return intensity;
}

void PointLight::SetPosition(float x, float y, float z)
{
	position = { x, y, z };
}

