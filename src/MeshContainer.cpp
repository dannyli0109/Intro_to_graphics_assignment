#include "MeshContainer.h"

MeshContainer::MeshContainer(int index)
{
	this->name = "Mesh Container";
	this->selectedMesh = index;
	ResourceManager* resourceManager = ResourceManager::GetInstance();
	this->data = resourceManager->GetMesh(this->selectedMesh);
}

void MeshContainer::Update(float deltaTime)
{
	ResourceManager* resourceManager = ResourceManager::GetInstance();
	data = resourceManager->GetMesh(selectedMesh);
}

void MeshContainer::Draw()
{
	data->Bind();
	data->Draw();
}

void MeshContainer::DrawGui()
{
	if (ImGui::CollapsingHeader(name.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
	{
		ResourceManager* resourceManager = ResourceManager::GetInstance();
		std::vector<MeshData*> meshes = resourceManager->GetMeshes();
		if (meshes.size() > selectedMesh)
		{
			std::vector<std::string> meshNames;
			for (MeshData* mesh : meshes)
			{
				meshNames.push_back(mesh->GetName());
			}

			ImGui::ListBox("Meshes", &selectedMesh, VectorOfStringGetter, static_cast<void*>(&meshNames), meshNames.size());
		}
	}
}
