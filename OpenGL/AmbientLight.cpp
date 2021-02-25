#include "AmbientLight.h"

AmbientLight::AmbientLight(glm::vec3 intensity)
{
	this->intensity = intensity;
}

glm::vec3 AmbientLight::GetIntensity()
{
	return intensity;
}
