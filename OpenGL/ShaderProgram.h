#pragma once
#include "Graphics.h"
#include "Utilities.h"
#include "Texture.h"
#include <iostream>
#include "GameObject.h"

class ShaderProgram
{
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint shaderProgram;

	bool everythingIsOkay = false;

public:
	ShaderProgram() {};
	ShaderProgram(std::string vertexFilename, std::string fragmentFilename);
	void UseShader();
	GLuint GetUniformLocation(std::string varname);
	void SetUniform(std::string varname, float value);
	void SetUniform(std::string varname, glm::mat4 value);
	void SetUniform(std::string varName, glm::vec4 value);
	void SetUniform(std::string varName, int value);
	void SetUniform(std::string varName, glm::vec3 value);
};

