#include "ResourceManager.h"

ResourceManager* ResourceManager::GetInstance()
{
	return instance;
}

ResourceManager* ResourceManager::CreateInstance()
{
	if (!instance)
	{
		instance = new ResourceManager();
	}
	return instance;
}
void ResourceManager::AddMesh(MeshData* mesh)
{
	meshes.push_back(mesh);
}
void ResourceManager::AddTexture(std::string name, Texture* texture)
{
	textureDictionary[name] = texture;
}
Texture* ResourceManager::GetTexture(std::string name)
{
	return textureDictionary[name];
}
MeshData* ResourceManager::GetMesh(int intex)
{
	return meshes[intex];
}
const std::vector<MeshData*>& ResourceManager::GetMeshes()
{
	return meshes;
}
const std::map<std::string, Texture*>& ResourceManager::GetTextureDict()
{
	return textureDictionary;
}
void ResourceManager::DrawGUI()
{
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
void ResourceManager::Destroy()
{
	for (auto it = textureDictionary.begin(); it != textureDictionary.end(); it++)
	{
		delete it->second;
	}

	for (MeshData* mesh : meshes)
	{
		delete mesh;
	}
	delete instance;
	instance = nullptr;
}
ResourceManager* ResourceManager::instance = nullptr;
