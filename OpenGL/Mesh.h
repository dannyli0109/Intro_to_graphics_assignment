#pragma once
#include "Graphics.h"
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 vertTangent;
	glm::vec3 vertBitangent;
	glm::vec3 color;
	glm::vec2 uv;
};

struct Material
{
	glm::vec3 ka;
	glm::vec3 kd;
	glm::vec3 ks;
};


class Mesh
{
public:
	Mesh(glm::vec3 color);
	Mesh(std::string fileName);
	virtual ~Mesh();

	void InitialiseMesh(unsigned int vertexCount, const Vertex* vertices, unsigned int indexCount, unsigned short* indices);

	virtual void Draw();

	void Bind();
	static void Unbind();
private:
	GLuint triCount;
	GLuint vao, vbo, ibo;
};

