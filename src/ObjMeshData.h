#pragma once
#include "MeshData.h"
#include "Utilities.h"
#include <string>
class ObjMeshData :
	public MeshData
{
public:
	ObjMeshData(std::string name, std::string fileName);
};

