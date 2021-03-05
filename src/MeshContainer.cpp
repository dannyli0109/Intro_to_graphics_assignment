#include "MeshContainer.h"

/**
 * Material base class, holds a pointer to the shader program, each material is corrispond to a single shader.
 */
/**
* Use the id to get the mesh data from the resource manager.
* So that the mesh data only loaded once per execute not per entity.
*
* \param id
*/
MeshContainer::MeshContainer(std::string id)
{
	this->name = "Mesh Container";
	ResourceManager* resourceManager = ResourceManager::GetInstance();
	this->selectedMesh = resourceManager->GetMeshIndex(id);
	this->data = resourceManager->GetMesh(this->selectedMesh);
}

void MeshContainer::Update(float deltaTime)
{
	ResourceManager* resourceManager = ResourceManager::GetInstance();
	data = resourceManager->GetMesh(selectedMesh);
}

void MeshContainer::Draw()
{
	Transform* transform = entity->GetComponent<Transform>();
	if (data && transform)
	{
		data->Bind();
		data->Draw();
	}
}

void MeshContainer::DrawGui()
{
	ResourceManager* resourceManager = ResourceManager::GetInstance();
	std::vector<std::string> meshNames = resourceManager->GetMeshNames();
	if (meshNames.size() > selectedMesh)
	{
		ImGui::ListBox("Meshes", &selectedMesh, VectorOfStringGetter, static_cast<void*>(&meshNames), meshNames.size());
	}
}

MeshContainer* MeshContainer::Create(std::string id)
{
	return new MeshContainer(id);
}
