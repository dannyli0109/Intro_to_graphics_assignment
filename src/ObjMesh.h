#pragma once
#include "Mesh.h"
#include "GUI.h"

class ShaderProgram;

class ObjMesh : public Mesh
{
public:
	ObjMesh(std::string fileName);
	virtual void DrawGui() override;

private:
	std::string fileName;
};

