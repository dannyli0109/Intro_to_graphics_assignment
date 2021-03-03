#include "CubeMeshData.h"

CubeMeshData::CubeMeshData()
{
	std::vector<Vertex> vertices = {
	{ {-0.5, -0.5, 0.5}, {0, 0, 1}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0} },
	{ {-0.5, 0.5, 0.5}, {0, 0, 1}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 1} },
	{ {0.5, 0.5, 0.5}, {0, 0, 1}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {1, 1} },
	{ {0.5, -0.5, 0.5}, {0, 0, 1}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {1, 0} },

	{ {-0.5, -0.5, -0.5}, {0, 0, -1}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0} },
	{ {-0.5, 0.5, -0.5}, {0, 0, -1}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 1} },
	{ {0.5, 0.5, -0.5}, {0, 0, -1}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {1, 1} },
	{ {0.5, -0.5, -0.5}, {0, 0, -1}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {1, 0} },

	{ {-0.5, -0.5, -0.5}, {-1, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0} },
	{ {-0.5, -0.5, 0.5}, {-1, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 1} },
	{ {-0.5, 0.5, 0.5}, {-1, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {1, 1} },
	{ {-0.5, 0.5, -0.5}, {-1, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {1, 0} },

	{ {0.5, -0.5, -0.5}, {1, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0} },
	{ {0.5, -0.5, 0.5}, {1, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 1} },
	{ {0.5, 0.5, 0.5}, {1, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {1, 1} },
	{ {0.5, 0.5, -0.5}, {1, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {1, 0} },

	{ {-0.5, -0.5, -0.5}, {0, -1, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0} },
	{ {-0.5, -0.5, 0.5}, {0, -1, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 1} },
	{ {0.5, -0.5, 0.5}, {0, -1, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {1, 1} },
	{ {0.5, -0.5, -0.5}, {0, -1, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {1, 0} },

	{ {-0.5, 0.5, -0.5}, {0,  1, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0} },
	{ {-0.5, 0.5, 0.5}, {0,  1, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 1} },
	{ {0.5, 0.5, 0.5}, {0,  1, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {1, 1} },
	{ {0.5, 0.5, -0.5}, {0,  1, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {1, 0} }
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
