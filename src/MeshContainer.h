#pragma once
#include "Component.h"
#include "MeshData.h"
#include "Utilities.h"
#include "ResourceManager.h"
class MeshContainer :
	public Component
{
public:
	MeshContainer(int index);
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	virtual void DrawGui() override;
private:
	int selectedMesh;
	MeshData* data = nullptr;
};