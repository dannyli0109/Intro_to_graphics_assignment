#include "MeshContainer.h"

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
	if (data)
	{
		data->Bind();
		data->Draw();
	}
}

void MeshContainer::DrawGui()
{
	if (ImGui::CollapsingHeader(name.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
	{
		ResourceManager* resourceManager = ResourceManager::GetInstance();
		std::vector<std::string> meshNames = resourceManager->GetMeshNames();
		if (meshNames.size() > selectedMesh)
		{
			ImGui::ListBox("Meshes", &selectedMesh, VectorOfStringGetter, static_cast<void*>(&meshNames), meshNames.size());
		}
	}
}
