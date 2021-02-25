#pragma once

#include <string>
#include "Graphics.h"

std::string LoadFileAsString(std::string filename);
float Lerp(float n1, float n2, float t);
void OnWindowSizeChange(GLFWwindow* window, int newWidth, int newHeight);
//Mesh LoadMesh();
