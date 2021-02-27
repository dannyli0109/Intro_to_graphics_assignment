#include "ShaderProgram.h"


ShaderProgram::~ShaderProgram()
{
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteProgram(shaderProgram);
}

ShaderProgram::ShaderProgram(std::string vertexFilename, std::string fragmentFilename)
{
	everythingIsOkay = true;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	shaderProgram = glCreateProgram();

	std::string vertexSource = LoadFileAsString(vertexFilename);
	std::string fragmentSource = LoadFileAsString(fragmentFilename);

	const char* vertexSourceC = vertexSource.c_str();
	glShaderSource(vertexShader, 1, &vertexSourceC, nullptr);
	glCompileShader(vertexShader);
	
	GLchar errorLog[512];
	GLint compileSuccess = 0;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compileSuccess);

	if (!compileSuccess)
	{
		std::cout << "vertex shader " << vertexFilename << " fail because..." << std::endl;
		glGetShaderInfoLog(vertexShader, 512, nullptr, errorLog);
		std::cout << errorLog << std::endl;
		everythingIsOkay = false;
	}
	else 
	{
		std::cout << "Everything is okay (with the vertex shader at least)" << std::endl;
	}

	const char* fragmentSourceC = fragmentSource.c_str();
	glShaderSource(fragmentShader, 1, &fragmentSourceC, nullptr);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compileSuccess);

	if (!compileSuccess)
	{
		std::cout << "fragment shader " << fragmentFilename << " fail because..." << std::endl;
		glGetShaderInfoLog(fragmentShader, 512, nullptr, errorLog);
		std::cout << errorLog << std::endl;
		everythingIsOkay = false;
	}
	else
	{
		std::cout << "Everything is okay (with the fragment shader at least)" << std::endl;
	}

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &compileSuccess);

	if (!compileSuccess)
	{
		std::cout << "The linking fail because..." << std::endl;
		glGetProgramInfoLog(shaderProgram, 512, nullptr, errorLog);
		std::cout << errorLog << std::endl;
		everythingIsOkay = false;
	}

	if (everythingIsOkay)
	{
		std::cout << "It appears that things are pretty okay" << std::endl;
	}

}

void ShaderProgram::UseShader()
{
	glUseProgram(shaderProgram);
}

GLuint ShaderProgram::GetUniformLocation(std::string varname)
{
	return glGetUniformLocation(shaderProgram, varname.c_str());
}

void ShaderProgram::SetUniform(std::string varname, float value)
{
	GLuint varloc = glGetUniformLocation(shaderProgram, varname.c_str());
	UseShader();
	glUniform1f(varloc, value);
}

void ShaderProgram::SetUniform(std::string varname, glm::mat4 value)
{
	GLuint varloc = glGetUniformLocation(shaderProgram, varname.c_str());
	UseShader();
	glUniformMatrix4fv(varloc, 1, GL_FALSE, &value[0][0]);
}

void ShaderProgram::SetUniform(std::string varName, glm::vec4 value)
{
	GLuint varLoc = glGetUniformLocation(shaderProgram, varName.c_str());
	UseShader();
	glUniform4fv(varLoc, 1, &value[0]);
}

void ShaderProgram::SetUniform(std::string varName, int value)
{
	GLuint varloc = glGetUniformLocation(shaderProgram, varName.c_str());
	UseShader();
	glUniform1i(varloc, value);
}

void ShaderProgram::SetUniform(std::string varName, glm::vec3 value)
{
	GLuint varLoc = glGetUniformLocation(shaderProgram, varName.c_str());
	UseShader();
	glUniform3fv(varLoc, 1, &value[0]);
}

