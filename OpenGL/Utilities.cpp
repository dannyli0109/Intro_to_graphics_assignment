#include "Utilities.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::string LoadFileAsString(std::string filename)
{
	std::fstream ifs;
	ifs.open(filename, std::ios::in);
	std::stringstream ss;

	if (ifs.is_open())
	{
		std::string line;
		while (std::getline(ifs, line))
		{
			ss << line << std::endl;
		}
		ifs.close();
	}
	return ss.str();
}

float Lerp(float n1, float n2, float t)
{
	return n1 * (1 - t) + n2 * t;
}

void OnWindowSizeChange(GLFWwindow* window, int newWidth, int newHeight)
{
	glViewport(0, 0, newWidth, newHeight);
}
