#include "Utilities.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::string LoadFileAsString(std::string filename)
{
	std::stringstream fileSoFar;
	std::ifstream file(filename);

	if (file.is_open())
	{
		while (!file.eof())
		{
			std::string thisLine;
			std::getline(file, thisLine);
			fileSoFar << thisLine << std::endl;
		}
		return fileSoFar.str();
	}
	else
	{
		std::cout << "Error loading file: " << filename << std::endl;
		return "";
	}
}

float Lerp(float n1, float n2, float t)
{
	return n1 * (1 - t) + n2 * t;
}

void OnWindowSizeChange(GLFWwindow* window, int newWidth, int newHeight)
{
	glViewport(0, 0, newWidth, newHeight);
}
