#include "QuadMesh.h"


QuadMesh::QuadMesh()
{
	this->name = "Quad Mesh";

	std::vector<Vertex> vertices = {
		{ {-0.5f, 0.5f, 0.5f}, {0, 0, 1}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0} },
		{ {0.5f, 0.5f, 0.5f}, {0, 0, 1}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {1, 0} },
		{ {-0.5f, -0.5f, 0.5f}, {0, 0, 1}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 1} },
		{ {0.5f, -0.5f, 0.5f}, {0, 0, 1}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {1, 1} }
	};

	//These are our indices - every three indices is a triangle, and refers to a position (a row of numbers) in the above vert array.
	std::vector<unsigned short> indices = {
		0, 1, 2, 1, 3, 2
	};

	InitialiseMesh(vertices.size(), vertices.data(), indices.size(), indices.data());
}