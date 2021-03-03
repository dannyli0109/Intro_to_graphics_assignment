#pragma once
#include "Graphics.h"
#include <string>
struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 vertTangent;
	glm::vec3 vertBitangent;
	glm::vec3 color;
	glm::vec2 uv;
};

class MeshData
{
public:
	virtual void InitialiseMesh(unsigned int vertexCount, const Vertex* vertices, unsigned int indexCount, unsigned short* indices);
	virtual ~MeshData();
	MeshData(const MeshData& other) = delete;
	MeshData& operator= (const MeshData& other) = delete;
	virtual void Draw();
	virtual void Bind();
	static void Unbind();
	std::string GetName();

protected:
	MeshData(std::string name) {
		this->name = name;
	};
	GLuint verticesID;
	GLuint indicesID;
	GLuint vao;
	GLuint triCount;
	std::string name;
};

