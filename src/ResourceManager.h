#pragma once
#include "MeshData.h"
#include "Texture.h"
#include <unordered_map>

class ResourceManager
{
public:
	static ResourceManager* GetInstance();
	static ResourceManager* CreateInstance();
	void AddMesh(std::string name, MeshData* mesh);
	void AddTexture(std::string name, Texture* texture);
	Texture* GetTexture(std::string name);
	MeshData* GetMesh(std::string mesh);
	void Destroy();
private:
	ResourceManager() {};
	~ResourceManager() {};
	static ResourceManager* instance;
	std::unordered_map<std::string, MeshData*> meshDictionary;
	std::unordered_map<std::string, Texture*> textureDictionary;
};

