#include "Mesh.h"

/*
struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 vertTangent;
	glm::vec3 vertBitangent;
	glm::vec3 color;
	glm::vec2 uv;
};
*/

Mesh::Mesh(glm::vec3 color)
{
	std::vector<Vertex> vertices = {
		{ {-0.5, -0.5, 0.5}, {0, 0, 1}, {0, 0, 0}, {0, 0, 0}, color, {0, 0} },
		{ {-0.5, 0.5, 0.5}, {0, 0, 1}, {0, 0, 0}, {0, 0, 0}, color, {0, 1} },
		{ {0.5, 0.5, 0.5}, {0, 0, 1}, {0, 0, 0}, {0, 0, 0}, color, {1, 1} },
		{ {0.5, -0.5, 0.5}, {0, 0, 1}, {0, 0, 0}, {0, 0, 0}, color, {1, 0} },

		{ {-0.5, -0.5, -0.5}, {0, 0, -1}, {0, 0, 0}, {0, 0, 0}, color, {0, 0} },
		{ {-0.5, 0.5, -0.5}, {0, 0, -1}, {0, 0, 0}, {0, 0, 0}, color, {0, 1} },
		{ {0.5, 0.5, -0.5}, {0, 0, -1}, {0, 0, 0}, {0, 0, 0}, color, {1, 1} },
		{ {0.5, -0.5, -0.5}, {0, 0, -1}, {0, 0, 0}, {0, 0, 0}, color, {1, 0} },

		{ {-0.5, -0.5, -0.5}, {-1, 0, 0}, {0, 0, 0}, {0, 0, 0}, color, {0, 0} },
		{ {-0.5, -0.5, 0.5}, {-1, 0, 0}, {0, 0, 0}, {0, 0, 0}, color, {0, 1} },
		{ {-0.5, 0.5, 0.5}, {-1, 0, 0}, {0, 0, 0}, {0, 0, 0}, color, {1, 1} },
		{ {-0.5, 0.5, -0.5}, {-1, 0, 0}, {0, 0, 0}, {0, 0, 0}, color, {1, 0} },

		{ {0.5, -0.5, -0.5}, {1, 0, 0}, {0, 0, 0}, {0, 0, 0}, color, {0, 0} },
		{ {0.5, -0.5, 0.5}, {1, 0, 0}, {0, 0, 0}, {0, 0, 0}, color, {0, 1} },
		{ {0.5, 0.5, 0.5}, {1, 0, 0}, {0, 0, 0}, {0, 0, 0}, color, {1, 1} },
		{ {0.5, 0.5, -0.5}, {1, 0, 0}, {0, 0, 0}, {0, 0, 0}, color, {1, 0} },

		{ {-0.5, -0.5, -0.5}, {0, -1, 0}, {0, 0, 0}, {0, 0, 0}, color, {0, 0} },
		{ {-0.5, -0.5, 0.5}, {0, -1, 0}, {0, 0, 0}, {0, 0, 0}, color, {0, 1} },
		{ {0.5, -0.5, 0.5}, {0, -1, 0}, {0, 0, 0}, {0, 0, 0}, color, {1, 1} },
		{ {0.5, -0.5, -0.5}, {0, -1, 0}, {0, 0, 0}, {0, 0, 0}, color, {1, 0} },

		{ {-0.5, 0.5, -0.5}, {0,  1, 0}, {0, 0, 0}, {0, 0, 0}, color, {0, 0} },
		{ {-0.5, 0.5, 0.5}, {0,  1, 0}, {0, 0, 0}, {0, 0, 0}, color, {0, 1} },
		{ {0.5, 0.5, 0.5}, {0,  1, 0}, {0, 0, 0}, {0, 0, 0}, color, {1, 1} },
		{ {0.5, 0.5, -0.5}, {0,  1, 0}, {0, 0, 0}, {0, 0, 0}, color, {1, 0} }
	};

	
	//These are our indices - every three indices is a triangle, and refers to a position (a row of numbers) in the above vert array.
	std::vector<unsigned short> indices = {
		0, 1, 2, 2, 3, 0,
		4, 5, 6, 6, 7, 4,
		8, 9, 10, 10, 11, 8,
		12, 13, 14, 14, 15, 12,
		16, 17, 18, 18, 19, 16,
		20, 21, 22, 22, 23, 20
	};


	
	InitialiseMesh(vertices.size(), vertices.data(), indices.size(), indices.data());

}

Mesh::Mesh(std::string fileName)
{
	Assimp::Importer importer;
	const aiScene* soulspearScene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	std::vector<Vertex> vertices;
	std::vector<unsigned short> indices;
	aiMesh* meshInfo = soulspearScene->mMeshes[0];
	vertices.reserve(meshInfo->mNumVertices);
	indices.reserve(meshInfo->mNumFaces);

	for (int i = 0; i < meshInfo->mNumVertices; i++)
	{
		Vertex newVertex;
		newVertex.position = { meshInfo->mVertices[i].x, meshInfo->mVertices[i].y, meshInfo->mVertices[i].z };

		if (meshInfo->HasVertexColors(0))
		{
			newVertex.color = { meshInfo->mColors[0][i].r,meshInfo->mColors[0][i].g,meshInfo->mColors[0][i].b };
		}
		else {
			newVertex.color = { 1.0f, 1.0f, 1.0f };
		}

		if (meshInfo->HasTextureCoords(0))
		{
			newVertex.uv = { meshInfo->mTextureCoords[0][i].x, meshInfo->mTextureCoords[0][i].y };
		}
		else {
			newVertex.uv = { newVertex.position.x, newVertex.position.y };
		}

		if (meshInfo->HasNormals())
		{
			newVertex.normal = { meshInfo->mNormals[i].x, meshInfo->mNormals[i].y, meshInfo->mNormals[i].z };
		}
		else {
			newVertex.normal = { 0, 0, 0 };
		}

		if (meshInfo->HasTangentsAndBitangents())
		{
			newVertex.vertTangent = { meshInfo->mTangents[i].x, meshInfo->mTangents[i].y, meshInfo->mTangents[i].z };
			newVertex.vertBitangent = { meshInfo->mBitangents[i].x, meshInfo->mBitangents[i].y, meshInfo->mBitangents[i].z };
		}
		else {
			newVertex.vertTangent = { 0, 0, 0 };
			newVertex.vertBitangent = { 0, 0, 0 };
		}
		vertices.push_back(newVertex);
	}
	//aiMaterial* material = soulspearScene->mMaterials[meshInfo->mMaterialIndex];

	//aiColor3D color;
	//material->Get(AI_MATKEY_COLOR_DIFFUSE, color);

	for (int i = 0; i < meshInfo->mNumFaces; i++)
	{
		indices.push_back(meshInfo->mFaces[i].mIndices[0]);
		indices.push_back(meshInfo->mFaces[i].mIndices[1]);
		indices.push_back(meshInfo->mFaces[i].mIndices[2]);
	}
	InitialiseMesh(vertices.size(), vertices.data(), indices.size(), indices.data());
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}

void Mesh::InitialiseMesh(
	unsigned int vertexCount,
	const Vertex* vertices,
	unsigned int indexCount,
	unsigned short* indices
)
{
	// generate buffers
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	// bind vertex array
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(vao);
	if (indexCount != 0)
	{
		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned short), indices, GL_STATIC_DRAW);
		triCount = indexCount / 3;
	}
	else {
		triCount = vertexCount / 3;
	}

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
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

void Mesh::Draw()
{
	if (ibo != 0)
	{
		glDrawElements(GL_TRIANGLES, 3 * triCount, GL_UNSIGNED_SHORT, 0);
	}
	else {
		glDrawArrays(GL_TRIANGLES, 0, 3 * triCount);
	}
}

void Mesh::Bind()
{
	glBindVertexArray(vao);
}

void Mesh::Unbind()
{
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
