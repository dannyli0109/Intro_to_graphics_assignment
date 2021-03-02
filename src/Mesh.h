#pragma once
#include "Graphics.h"
#include "ShaderProgram.h"
#include <vector>
#include "Component.h"
#include "Material.h"
#include "Transform.h"
#include "Entity.h"

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 vertTangent;
	glm::vec3 vertBitangent;
	glm::vec3 color;
	glm::vec2 uv;
};

//struct Material
//{
//	glm::vec3 ka;
//	glm::vec3 kd;
//	glm::vec3 ks;
//
//	float specularPower;
//};

class Mesh : public Component
{
public:
	Mesh() {
		this->name = "Mesh";
	};
	virtual void InitialiseMesh(unsigned int vertexCount, const Vertex* vertices, unsigned int indexCount, unsigned short* indices);
	virtual ~Mesh();
	Mesh(const Mesh& other) = delete;
	Mesh& operator= (const Mesh& other) = delete;
	virtual void Draw() override;

	virtual void Bind();
	static void Unbind();

	GLuint verticesID;
	GLuint indicesID;
	GLuint vao;
	GLuint triCount;
};

