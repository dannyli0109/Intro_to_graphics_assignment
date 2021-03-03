#pragma once
#include <fstream>
#include <sstream>
#include <iostream>
#include "Graphics.h"
#include <vector>
#include "FrameBuffer.h"

std::string LoadFileAsString(std::string filename);
//void OnWindowSizeChange(GLFWwindow* window, int newWidth, int newHeight, FrameBuffer* frameBuffer);
std::vector<std::string> Split(const std::string& s, std::string delimiter);
void ParseObj(
	std::string filename,
	std::vector<glm::vec3>& verts, std::vector<unsigned short>& vertIndices,
	std::vector<glm::vec2>& uvs, std::vector<unsigned short>& uvIndices,
	std::vector<glm::vec3>& normals, std::vector<unsigned short>& normalIndices,
	bool flipUV
);