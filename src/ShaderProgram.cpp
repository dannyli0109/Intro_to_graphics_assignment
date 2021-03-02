#include "ShaderProgram.h"

ShaderProgram::~ShaderProgram()
{
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteProgram(program);
}

GLuint ShaderProgram::GetId()
{
	return program;
}

ShaderProgram::ShaderProgram(std::string vertexFilename, std::string fragmentFilename)
{
	this->created = true;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	program = glCreateProgram();

	std::string vertexSource = LoadFileAsString(vertexFilename);
	std::string fragmentSource = LoadFileAsString(fragmentFilename);

	const char* vertexSourceC = vertexSource.c_str();
	int vertexSourceLength = (int)vertexSource.size();

	glShaderSource(vertexShader, 1, &vertexSourceC, &vertexSourceLength);
	glCompileShader(vertexShader);

	GLchar errorLog[256];
	GLint compileSuccess;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compileSuccess);
	if (compileSuccess == GL_FALSE)
	{
		std::cout << "Error compiling vertex shader: " << vertexFilename << std::endl;
		glGetShaderInfoLog(vertexShader, 256, nullptr, errorLog);
		std::cout << errorLog;
		created = false;
	}

	const char* fragmentSourceC = fragmentSource.c_str();
	int fragmentSourceeLength = (int)fragmentSource.size();

	glShaderSource(fragmentShader, 1, &fragmentSourceC, &fragmentSourceeLength);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compileSuccess);
	if (compileSuccess == GL_FALSE)
	{
		std::cout << "Error compiling fragment shader: " << fragmentFilename << std::endl;
		glGetShaderInfoLog(fragmentShader, 256, nullptr, errorLog);
		std::cout << errorLog;
		created = false;
	}


	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &compileSuccess);

	if (compileSuccess == GL_FALSE)
	{
		std::cout << "Error linking shaders: " << vertexFilename << " and " << fragmentFilename << std::endl;
		glGetProgramInfoLog(program, 256, nullptr, errorLog);
		std::cout << errorLog;
		created = false;
	}

	if (created)
	{
		std::cout << "Successfully loaded/linked shaders " << vertexFilename << " and " << fragmentFilename << "!" << std::endl;
	}
}

void ShaderProgram::UseShader()
{
	glUseProgram(program);
	activeShader = program;
}

GLuint ShaderProgram::GetUniformLocation(std::string varname)
{
	return glGetUniformLocation(program, varname.c_str());
}

void ShaderProgram::SetUniform(std::string varname, float value)
{
	GLuint varloc = glGetUniformLocation(program, varname.c_str());
	UseShader();
	glUniform1f(varloc, value);
}
void ShaderProgram::SetUniform(std::string varname, glm::mat4 value)
{
	GLuint varloc = glGetUniformLocation(program, varname.c_str());
	UseShader();
	glUniformMatrix4fv(varloc, 1, GL_FALSE, &value[0][0]);
}

void ShaderProgram::SetUniform(std::string varName, glm::vec4 value)
{
	GLuint varLoc = glGetUniformLocation(program, varName.c_str());
	UseShader();
	glUniform4fv(varLoc, 1, &value[0]);
}

void ShaderProgram::SetUniform(std::string varName, int value)
{
	GLuint varloc = glGetUniformLocation(program, varName.c_str());
	UseShader();
	glUniform1i(varloc, value);
}

void ShaderProgram::SetUniform(std::string varName, glm::vec3 value)
{
	GLuint varLoc = glGetUniformLocation(program, varName.c_str());
	UseShader();
	glUniform3fv(varLoc, 1, &value[0]);
}
GLuint ShaderProgram::activeShader = 0;
