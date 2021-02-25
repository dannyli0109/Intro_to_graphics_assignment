#pragma once
#include "Graphics.h"
class AmbientLight
{
public:
	AmbientLight(glm::vec3 intensity);
	glm::vec3 GetIntensity();
private:
	glm::vec3 intensity;
};

