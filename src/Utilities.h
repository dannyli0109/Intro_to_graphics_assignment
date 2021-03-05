#pragma once
#include <fstream>
#include <sstream>
#include <iostream>
#include "Graphics.h"
#include <vector>
#include "FrameBuffer.h"

/**
 * Load the a file and output the string.
 * 
 * \param filename Path of the file to load
 */
std::string LoadFileAsString(std::string filename);

/**
 * Splitting a string to an array by the delimiter.
 * 
 * \param s string to split
 * \param delimiter defines when the split happens
 */
std::vector<std::string> Split(const std::string& s, std::string delimiter);

/**
 * Parse obj file and return a bunch of vertex data.
 * The function only handles vertex position, uvs and normals, and ignore everything else in the obj file.
 *
 * \param filename Obj file path
 * \param verts vertex position get from the obj file
 * \param vertIndices vertex index get from the obj file
 * \param uvs UV coordinates get from the obj file
 * \param uvIndices uv indices get from the obj file
 * \param normals normal data get from the obj file
 * \param normal indices get from the obj file
 * \param flipUV whether we flip the y coordinates of the uv
 */
void ParseObj(
	std::string filename,
	std::vector<glm::vec3>& verts, std::vector<unsigned short>& vertIndices,
	std::vector<glm::vec2>& uvs, std::vector<unsigned short>& uvIndices,
	std::vector<glm::vec3>& normals, std::vector<unsigned short>& normalIndices,
	bool flipUV
);

bool VectorOfStringGetter(void* data, int n, const char** out_text);

