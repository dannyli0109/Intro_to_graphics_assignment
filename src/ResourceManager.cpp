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
void ResourceManager::AddMesh(std::string name, MeshData* mesh)
{
	meshDictionary[name] = mesh;
}
void ResourceManager::AddTexture(std::string name, Texture* texture)
{
	textureDictionary[name] = texture;
}
Texture* ResourceManager::GetTexture(std::string name)
{
	return textureDictionary[name];
}
MeshData* ResourceManager::GetMesh(std::string mesh)
{
	return meshDictionary[mesh];
}
void ResourceManager::Destroy()
{
	for (auto it = textureDictionary.begin(); it != textureDictionary.end(); it++)
	{
		delete it->second;
	}

	for (auto it = meshDictionary.begin(); it != meshDictionary.end(); it++)
	{
		delete it->second;
	}
	delete instance;
	instance = nullptr;
}
ResourceManager* ResourceManager::instance = nullptr;
