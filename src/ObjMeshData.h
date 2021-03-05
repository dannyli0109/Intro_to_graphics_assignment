#pragma once
#include "MeshData.h"
#include "Utilities.h"
#include <string>
class ObjMeshData :
	public MeshData
{
public:
	/**
	 * Loading mesh data from obj data.
	 * 
	 * \param fileName file name for the obj file
	 */
	ObjMeshData(std::string fileName);
};

