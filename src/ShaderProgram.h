#pragma once
#include "Graphics.h"
#include <string>
#include <iostream>
#include "Utilities.h"

class ShaderProgram
{
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint program;

	bool created = false;

	std::string name = "";

public:
	~ShaderProgram();

	ShaderProgram(const ShaderProgram& other) = delete;
	ShaderProgram& operator= (const ShaderProgram& other) = delete;
	GLuint GetId();


	ShaderProgram(std::string vertexFilename, std::string fragmentFilename);
	void UseShader();
	GLuint GetUniformLocation(std::string varname);
	void SetUniform(std::string varname, float value);
	void SetUniform(std::string varname, glm::mat4 value);
	void SetUniform(std::string varName, glm::vec4 value);
	void SetUniform(std::string varName, int value);
	void SetUniform(std::string varName, glm::vec3 value);

	static GLuint activeShader;

	std::string GetName();
	void SetName(std::string name);
};