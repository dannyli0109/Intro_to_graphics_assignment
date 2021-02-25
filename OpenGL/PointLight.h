#pragma once
#include "Graphics.h"

class PointLight
{
public:
	PointLight(glm::vec3 position, glm::vec3 color);
	glm::vec3 GetPosition();
	glm::vec3 GetIntensity();
	void SetPosition(float x, float y, float z);

private:
	glm::vec3 position;
	glm::vec3 intensity;
};

