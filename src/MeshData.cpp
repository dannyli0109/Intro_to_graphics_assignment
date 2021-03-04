#include "MeshData.h"

void MeshData::InitialiseMesh(unsigned int vertexCount, const Vertex* vertices, unsigned int indexCount, unsigned short* indices)
{
	// generate buffers
	glGenBuffers(1, &verticesID);
	glGenVertexArrays(1, &vao);

	// bind vertex array
	glBindBuffer(GL_ARRAY_BUFFER, verticesID);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(vao);
	if (indexCount != 0)
	{
		glGenBuffers(1, &indicesID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned short), indices, GL_STATIC_DRAW);
		triCount = indexCount / 3;
	}
	else {
		triCount = vertexCount / 3;
	}

	glBindBuffer(GL_ARRAY_BUFFER, verticesID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Vertex::normal));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Vertex::vertTangent));
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Vertex::vertBitangent));
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Vertex::color));
	glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Vertex::uv));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	glEnableVertexAttribArray(5);

	Unbind();
}

MeshData::~MeshData()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &verticesID);
	glDeleteBuffers(1, &indicesID);
}

void MeshData::SetName(std::string name)
{
	this->name = name;
}

std::string MeshData::GetName()
{
	return name;
}

void MeshData::Draw()
{
	if (indicesID != 0)
	{
		glDrawElements(GL_TRIANGLES, 3 * triCount, GL_UNSIGNED_SHORT, 0);
	}
	else {
		glDrawArrays(GL_TRIANGLES, 0, 3 * triCount);
	}
}

void MeshData::Bind()
{
	glBindVertexArray(vao);
}

void MeshData::Unbind()
{
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}