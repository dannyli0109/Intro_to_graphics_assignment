#pragma once
#include "Component.h"
#include "MeshData.h"
class MeshContainer :
	public Component
{
public:
	MeshContainer(MeshData* data) {
		this->name = "Mesh Container";
		this->data = data;
	};
	virtual void Draw() override;
private:
	MeshData* data;
};