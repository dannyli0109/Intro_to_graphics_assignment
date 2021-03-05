#pragma once
#include "Component.h"
#include "MeshData.h"
#include "Utilities.h"
#include "ResourceManager.h"
#include "Transform.h"
#include "Entity.h"


/**
 * Mesh Container component, doesn't contain the data itself, but it holds the mesh data pointer.
 */
class MeshContainer :
	public Component
{
public:
	/**
	 * Use the id to get the mesh data from the resource manager.
	 * So that the mesh data only loaded once per execute not per entity.
	 * 
	 * \param id
	 */
	MeshContainer(std::string id);
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	virtual void DrawGui() override;
	static MeshContainer* Create(std::string id);
private:
	int selectedMesh;
	MeshData* data = nullptr;
};