#include "ObjMeshData.h"

ObjMeshData::ObjMeshData(std::string fileName)
{
	std::vector<Vertex> vertices;
	std::vector<glm::vec3> verts;
	std::vector<unsigned short> indices;
	std::vector<glm::vec2> uvs;
	std::vector<unsigned short> uvIndices;
	std::vector<glm::vec3> normals;
	std::vector<unsigned short> normalIndices;

	// Super not bullet proof parser, it doesn't eliminate identical verts, but it's fine for now
	ParseObj(fileName, verts, indices, uvs, uvIndices, normals, normalIndices, true);

	for (int i = 0; i < verts.size(); i++)
	{
		Vertex newVert;
		newVert.position = verts[i];
		vertices.push_back(newVert);
	}

	for (int i = 0; i < indices.size(); i++)
	{
		if (uvIndices.size() > i)
		{
			vertices[indices[i]].uv = uvs[uvIndices[i]];
		}

		if (normalIndices.size() > i)
		{
			vertices[indices[i]].normal = normals[normalIndices[i]];
		}
	}


	// calculate tangent, bitangent
	for (int i = 0; i < indices.size(); i += 3)
	{
		for (int j = 0; j < 3; j++)
		{
			Vertex& v1 = vertices[indices[i + (j % 3)]];
			Vertex& v2 = vertices[indices[i + (j + 1) % 3]];
			Vertex& v3 = vertices[indices[i + (j + 2) % 3]];

			glm::vec3 edge1 = v2.position - v1.position;
			glm::vec3 edge2 = v3.position - v1.position;
			glm::vec2 deltaUV1 = v2.uv - v1.uv;
			glm::vec2 deltaUV2 = v3.uv - v1.uv;

			float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

			v1.vertTangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
			v1.vertTangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
			v1.vertTangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);

			//v1.vertTangent = glm::normalize(v1.vertTangent);

			v1.vertBitangent.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
			v1.vertBitangent.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
			v1.vertBitangent.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);

			//v1.vertBitangent = glm::normalize(v1.vertBitangent);
		}
	}

	InitialiseMesh(vertices.size(), vertices.data(), indices.size(), indices.data());
}
